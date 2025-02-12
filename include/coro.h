#include <fmt/base.h>
#include <fmt/std.h>
#include <atomic>
#include <cstddef>
#include <exception>
#include <functional>
#include <mutex>
#include <list>
#include <optional>
#include <coroutine>
#include <queue>
#include <utility>
#include <condition_variable>
#include <cpptrace/cpptrace.hpp>

struct Generater {
    struct promise_type {
        std::suspend_always initial_suspend() { return {}; }
        void return_void() {}
        void unhandled_exception() {}
        std::suspend_always final_suspend() noexcept { return {}; }
        Generater get_return_object() {
            return Generater{
                std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always await_transform(int v) {
            val = v;
            return {};
        }

        std::suspend_always yield_value(int v) {
            val = v;
            return {};
        }
        int val = -2;
    };

    // 只要自定义了析构函数，那么拷贝和移动必须要考虑
    explicit Generater(std::coroutine_handle<promise_type> h) : handle(h) {}
    Generater(Generater &&g) noexcept : handle(g.handle) { g.handle = {}; }
    Generater &operator=(Generater &&g) noexcept {
        handle.destroy();
        handle = g.handle;
        g.handle = {};
        return *this;
    }
    Generater(const Generater &g) = delete;
    Generater &operator=(const Generater &g) = delete;

    ~Generater() {
        if (handle) {
            handle.destroy();
        }
    }

    int next() {
        if (has_next()) {
            is_used = true;
            return handle.promise().val;
        }
        throw std::runtime_error("gg");
    }

    bool has_next() {
        // 卫语句，因为后面要调用handle，而handle在协程函数体结束后会根据final_suspend的判断决定是否销毁
        // 若为suspend_never,则一结束就自动销毁，此时调用done()会访问野指针
        // 若为suspend_always,则函数体结束后自动挂起(此时done()==true,但是promise没被销毁)
        if (handle.done()) {
            return false;
        }
        if (is_used) {
            handle.resume();
            is_used = false;
        }
        // resume之后返回done,说明运行的是协程函数体结尾的那段代码，这段代码不会设置新值
        return !handle.done();
    }

    std::coroutine_handle<promise_type>
        handle;           // 看成一个new出来的指针，需要调用distory
    bool is_used = true;  // 刚开始是已经用完的状态，需要得到新值
};

template <typename T>
struct Result {
    explicit Result() = default;

    explicit Result(T &&value) : _value(value) {}

    explicit Result(std::exception_ptr &&exception_ptr)
        : _value(exception_ptr) {}

    T get_or_throw() {
        T *v = std::get_if<0>(&_value);
        if (v == nullptr) [[unlikely]] {
            std::rethrow_exception(std::get<1>(_value));
        }
        return *v;
    }

   private:
    std::variant<T, std::exception_ptr> _value;
};

struct AbstractExecutor {
    virtual ~AbstractExecutor() = default;
    virtual void execute(std::function<void()> &&func) = 0;
};

struct InlineExecutor : AbstractExecutor {
    void execute(std::function<void()> &&func) override { func(); }
};

struct DetachExecutor : AbstractExecutor {
    void execute(std::function<void()> &&func) override {
        std::thread([func]() { func(); }).detach();
    }
};

class LooperExecutor : public AbstractExecutor {
   private:
    std::condition_variable queue_condition;
    std::mutex queue_lock;
    std::queue<std::function<void()>> executable_queue;

    std::atomic<bool> is_active;
    std::thread work_thread;

    void run_loop() {
        while (is_active.load(std::memory_order_relaxed) ||
               !executable_queue.empty()) {
            std::unique_lock lock(queue_lock);
            if (executable_queue.empty()) {
                queue_condition.wait(lock);
                if (executable_queue.empty()) {
                    continue;
                }
            }
            auto func = executable_queue.front();
            executable_queue.pop();
            lock.unlock();

            func();
        }
    }

   public:
    LooperExecutor() {
        is_active.store(true, std::memory_order_relaxed);
        work_thread = std::thread(&LooperExecutor::run_loop, this);
    }

    ~LooperExecutor() {
        shutdown(false);
        if (work_thread.joinable()) {
            work_thread.join();
        }
    }

    void execute(std::function<void()> &&func) override {
        std::unique_lock lock(queue_lock);
        if (is_active.load(std::memory_order_relaxed)) {
            executable_queue.push(func);
            lock.unlock();
            queue_condition.notify_one();
        }
    }

    void shutdown(bool wait_for_complete = true) {
        is_active.store(false, std::memory_order_relaxed);
        if (!wait_for_complete) {
            // clear queue.
            std::unique_lock lock(queue_lock);
            decltype(executable_queue) empty_queue;
            std::swap(executable_queue, empty_queue);
            lock.unlock();
        }

        queue_condition.notify_all();
    }
};

class SharedLooperExecutor : public AbstractExecutor {
   public:
    void execute(std::function<void()> &&func) override {
        static LooperExecutor sharedLooperExecutor;
        sharedLooperExecutor.execute(std::move(func));
    }
};

template <typename ResultType, typename ExecutorType = InlineExecutor>
class Task;
template <typename ResultType, typename ExecutorType>
struct TaskPromise;

struct DispatchAwaiter {
    explicit DispatchAwaiter(AbstractExecutor &e) : executor(e) {}
    bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
        executor.execute([handle]() { handle.resume(); });
    }
    void await_resume() noexcept {}

    AbstractExecutor &executor;
};

struct ResumeAwaiter {
    bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<>) noexcept {
        if (resume.has_value()) {
            resume.value()();
        }
    }
    void await_resume() noexcept {}

    std::optional<std::function<void()>> resume;
};

template <typename ResultType, typename ExecutorType>
struct TaskPromise {
    DispatchAwaiter initial_suspend() { return DispatchAwaiter{executor}; }

    // 等待协程调用完毕，才能调用resume
    // !不能在completion_callbacks中注册resume_callback
    // !因为task会在调用者的线程析构(即调用resume时所在的线程析构)
    // !如果在completion_callbacks中注册resume_callback,
    // !resume_callback会析构completion_callbacks,导致completion_callback在遍历中途被析构
    ResumeAwaiter final_suspend() noexcept {
        notify_callbacks();
        return ResumeAwaiter{std::move(resume_callback)};
    }

    Task<ResultType, ExecutorType> get_return_object() {
        return Task{std::coroutine_handle<TaskPromise>::from_promise(*this)};
    }

    void unhandled_exception() {
        std::lock_guard lock(result_lock);
        result = Result<ResultType>(std::current_exception());
        completion.notify_all();
    }

    // return_value在notify_callbackss中自己线程调用resume时，自己线程在await_resume()时会调用get_result()获得锁
    // 所以notify_callbacks()不需要加completion_lock锁

    void return_value(ResultType value) {
        std::lock_guard lock(result_lock);
        result = Result<ResultType>(std::move(value));
        completion.notify_all();

        fmt::println("thread_id:{},return value:{}", std::this_thread::get_id(),
                     value);
    }

    ResultType get_result() {
        // blocking for result or throw on exception
        std::unique_lock lock(result_lock);
        if (!result.has_value()) {
            completion.wait(lock);
        }
        return result->get_or_throw();
    }

    void on_completed(std::function<void(Result<ResultType>)> &&func) {
        // 有结果，直接调用
        {
            std::unique_lock lock(result_lock);
            if (result.has_value()) {
                auto value = result.value();
                lock.unlock();
                func(value);
                return;
            }
        }
        // 没结果，加入回调列表
        {
            std::lock_guard lock(callback_list_lock);
            completion_callbacks.push_back(func);
        }
    }

    AbstractExecutor &get_executor() { return executor; }

    void register_resume_callback(std::function<void()> &&func) {
        std::lock_guard lock(callback_list_lock);
        resume_callback = std::move(func);
    }
    void unregister_resume_callback() {
        std::lock_guard lock(callback_list_lock);
        resume_callback.reset();
    }

   private:
    std::optional<Result<ResultType>> result;

    std::mutex result_lock;
    std::condition_variable completion;

    std::list<std::function<void(Result<ResultType>)>> completion_callbacks;
    // 用于注册调用者的恢复函数
    std::optional<std::function<void()>> resume_callback;
    std::mutex callback_list_lock;
    ExecutorType executor;

    void notify_callbacks() {
        fmt::println("thread_id:{},notify_callbacks",
                     std::this_thread::get_id());
        {
            std::lock_guard lock(result_lock);
            if (!result.has_value()) {
                return;
            }
        }
        // 有结果时，不用加结果锁了，因为结果只会被设置一次
        // 但是回调列表需要加锁
        {
            std::lock_guard lock(callback_list_lock);
            auto value = result.value();
            for (auto &callback : completion_callbacks) {
                callback(result.value());
            }
            completion_callbacks.clear();
        }
    }
};
template <typename... Tasks>
struct WhenAllAwaiter {
    std::tuple<Tasks...> tasks;
    std::atomic<size_t> remaining{sizeof...(Tasks)};
    std::tuple<typename Tasks::result_type...> results;

    WhenAllAwaiter(Tasks... tasks)
        : tasks(std::make_tuple(std::move(tasks)...)) {}

    bool await_ready() const noexcept { return sizeof...(Tasks) == 0; }

    void await_suspend(std::coroutine_handle<> handle) {
        // 注册收集结果的回调
        [this]<size_t... I>(std::index_sequence<I...>) {
            (std::get<I>(tasks).then(
                 [this](auto result) { std::get<I>(results) = result; }),
             ...);
        }(std::index_sequence_for<Tasks...>{});
        // 注册恢复的回调
        [handle, this]<size_t... I>(std::index_sequence<I...>) {
            (std::get<I>(tasks).register_resume_callback([this, handle]() {
                if (--remaining == 0) {
                    handle.resume();
                }
            }),
             ...);
        }(std::index_sequence_for<Tasks...>{});
    }

    auto await_resume() { return results; }
};

template <typename... Tasks>
struct WhenAnyAwaiter {
    std::tuple<Tasks...> tasks;
    std::atomic<int> finished_index{-1};
    std::variant<typename Tasks::result_type...> results;

    WhenAnyAwaiter(Tasks... tasks)
        : tasks(std::make_tuple(std::move(tasks)...)) {}

    bool await_ready() const noexcept { return sizeof...(Tasks) == 0; }

    void await_suspend(std::coroutine_handle<> handle) {
        // 注册收集结果的回调
        [this]<size_t... I>(std::index_sequence<I...>) {
            (std::get<I>(tasks).then([this](auto result) {
                int origin_index = -1;
                int current_index = I;
                if (finished_index.compare_exchange_strong(origin_index,
                                                           current_index)) {
                    std::get<I>(results) = result;
                    // 解register其他的resume_callback
                    unregister_resume_callback();
                }
            }),
             ...);
        }(std::index_sequence_for<Tasks...>{});
        // 注册恢复的回调
        [handle, this]<size_t... I>(std::index_sequence<I...>) {
            (
                [i = I, this, handle]() {
                    if (finished_index == -1 || finished_index == i) {
                        std::get<I>(tasks).register_resume_callback(
                            [this, handle]() {
                                if (finished_index.load() == I) {
                                    handle.resume();
                                }
                            });
                    }
                }(),
                ...);
        }(std::index_sequence_for<Tasks...>{});
    }

    auto await_resume() { return results; }

    void unregister_resume_callback() {
        [this]<size_t... I>(std::index_sequence<I...>) {
            (
                [i = I, this]() {
                    if (finished_index != i) {
                        std::get<I>(tasks).unregister_resume_callback();
                    }
                }(),
                ...);
        }(std::index_sequence_for<Tasks...>{});
    }
};

template <typename ResultType, typename ExecutorType>
struct Task {
    template <typename... Tasks>
    friend struct WhenAllAwaiter;
    template <typename... Tasks>
    friend struct WhenAnyAwaiter;
    using promise_type = TaskPromise<ResultType, ExecutorType>;
    using result_type = ResultType;

    constexpr bool await_ready() const noexcept { return false; }

    template <typename _ResultType, typename _ExecutorType>
    void await_suspend(
        std::coroutine_handle<TaskPromise<_ResultType, _ExecutorType>>
            caller_handle) noexcept {
        // ! 协程的精髓:把自己的恢复运行能力交给被调用者

        // 用对方的执行器运行对方的恢复
        register_resume_callback([caller_handle]() {
            caller_handle.promise().get_executor().execute([caller_handle]() {
                fmt::println("thread_id:{},resume_begin",
                             std::this_thread::get_id());
                caller_handle.resume();
                fmt::println("thread_id:{},resume_end",
                             std::this_thread::get_id());
            });
        });
    }

    ResultType await_resume() noexcept { return get_result(); }

    ResultType get_result() { return promise().get_result(); }

    Task &then(std::function<void(ResultType)> &&func) {
        handle.promise().on_completed([func](auto result) {
            try {
                func(result.get_or_throw());
            } catch (std::exception &e) {
                // ignore.
            }
        });
        return *this;
    }

    Task &catching(std::function<void(std::exception &)> &&func) {
        handle.promise().on_completed([func](auto result) {
            try {
                result.get_or_throw();
            } catch (std::exception &e) {
                func(e);
            }
        });
        return *this;
    }

    Task &operator=(Task &&) = delete;
    explicit Task(std::coroutine_handle<promise_type> handle) noexcept
        : handle(handle) {}

    Task(Task &&task) noexcept : handle(std::exchange(task.handle, {})) {}

    Task(Task &) = delete;

    Task &operator=(Task &) = delete;

    ~Task() {
        if (handle) {
            fmt::println("~task()");
            handle.destroy();
            handle = {};
        }
    }

   private:
    promise_type &promise() { return handle.promise(); }
    std::coroutine_handle<promise_type> handle;
    void register_resume_callback(std::function<void()> &&func) {
        //! 如果自己已经结束，那么直接调用
        if (this->handle.done()) {
            func();
            return;
        }
        promise().register_resume_callback(std::move(func));
    }

    void unregister_resume_callback() {
        promise().unregister_resume_callback();
    }
};

template <typename... Tasks>
auto when_all(Tasks... tasks) {
    return WhenAllAwaiter{std::move(tasks)...};
}

template <typename... Tasks>
auto when_any(Tasks... tasks) {
    return WhenAnyAwaiter{std::move(tasks)...};
}
