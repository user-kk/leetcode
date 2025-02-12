#include <queue>
#include <mutex>
#include <functional>
#include <future>
#include <map>
#include <functional>
#include <mutex>
#include <list>
#include <optional>
#include <coroutine>
#include <utility>
#include <exception>
#include <fmt/base.h>
#include <fmt/std.h>

template <typename T>
struct Result {
    explicit Result() = default;

    explicit Result(T &&value) : _value(value) {}

    explicit Result(std::exception_ptr &&exception_ptr)
        : _exception_ptr(exception_ptr) {}

    T get_or_throw() {
        if (_exception_ptr) {
            std::rethrow_exception(_exception_ptr);
        }
        return _value;
    }

   private:
    T _value{};
    std::exception_ptr _exception_ptr;
};

class AbstractExecutor {
   public:
    virtual void execute(std::function<void()> &&func) = 0;
};

class NoopExecutor : public AbstractExecutor {
   public:
    void execute(std::function<void()> &&func) override { func(); }
};

class NewThreadExecutor : public AbstractExecutor {
   public:
    void execute(std::function<void()> &&func) override {
        auto g = std::thread([func]() {
            fmt::println("thread_id:{},execute", std::this_thread::get_id());
            func();
        });
        g.detach();
    }
};

class AsyncExecutor : public AbstractExecutor {
   public:
    void execute(std::function<void()> &&func) override {
        std::unique_lock lock(future_lock);
        auto id = nextId++;
        lock.unlock();

        auto future = std::async([this, id, func]() {
            func();

            std::unique_lock lock(future_lock);
            // move future to stack so that it will be destroyed after unlocked.
            auto f = std::move(this->futures[id]);
            this->futures.erase(id);
            lock.unlock();
        });

        lock.lock();
        this->futures[id] = std::move(future);
        lock.unlock();
    }

   private:
    std::mutex future_lock;
    int nextId = 0;
    std::map<int, std::future<void>> futures{};
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

struct DispatchAwaiter {
    explicit DispatchAwaiter(AbstractExecutor *executor) noexcept
        : _executor(executor) {}

    bool await_ready() const { return false; }

    void await_suspend(std::coroutine_handle<> handle) const {
        _executor->execute([handle]() { handle.resume(); });
    }

    void await_resume() {}

   private:
    AbstractExecutor *_executor;
};

template <typename ResultType, typename Executor>
struct Task;

template <typename Result, typename Executor>
struct TaskAwaiter {
    explicit TaskAwaiter(AbstractExecutor *executor,
                         Task<Result, Executor> &&task) noexcept
        : _executor(executor), task(std::move(task)) {}

    TaskAwaiter(TaskAwaiter &&completion) noexcept
        : _executor(completion._executor),
          task(std::exchange(completion.task, {})) {}

    TaskAwaiter(TaskAwaiter &) = delete;

    TaskAwaiter &operator=(TaskAwaiter &) = delete;

    constexpr bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
        task.finally([handle, this]() {
            _executor->execute([handle]() {
                fmt::println("thread_id:{},resume_begin",
                             std::this_thread::get_id());
                handle.resume();
                fmt::println("thread_id:{},resume_end",
                             std::this_thread::get_id());
            });
        });
    }

    Result await_resume() noexcept { return task.get_result(); }

   private:
    Task<Result, Executor> task;
    AbstractExecutor *_executor;
};

template <typename ResultType, typename Executor>
struct TaskPromise {
    DispatchAwaiter initial_suspend() { return DispatchAwaiter{&executor}; }

    std::suspend_always final_suspend() noexcept { return {}; }

    Task<ResultType, Executor> get_return_object() {
        return Task{std::coroutine_handle<TaskPromise>::from_promise(*this)};
    }

    template <typename _ResultType, typename _Executor>
    TaskAwaiter<_ResultType, _Executor> await_transform(
        Task<_ResultType, _Executor> &&task) {
        return TaskAwaiter<_ResultType, _Executor>(&executor, std::move(task));
    }

    void unhandled_exception() {
        std::lock_guard lock(result_lock);
        result = Result<ResultType>(std::current_exception());
        completion.notify_all();
        notify_callbacks();
    }

    void return_value(ResultType value) {
        std::lock_guard lock(result_lock);
        result = Result<ResultType>(std::move(value));
        completion.notify_all();
        notify_callbacks();
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
        std::unique_lock lock(result_lock);
        if (result.has_value()) {
            auto value = result.value();
            lock.unlock();
            func(value);
        } else {
            completion_callbacks.push_back(func);
        }
    }

   private:
    std::optional<Result<ResultType>> result;

    std::mutex result_lock;
    std::condition_variable completion;

    std::list<std::function<void(Result<ResultType>)>> completion_callbacks;

    Executor executor;

    void notify_callbacks() {
        auto value = result.value();
        for (auto &callback : completion_callbacks) {
            callback(value);
        }
        completion_callbacks.clear();
    }
};

template <typename ResultType, typename Executor = NewThreadExecutor>
struct Task {
    using promise_type = TaskPromise<ResultType, Executor>;

    ResultType get_result() { return handle.promise().get_result(); }

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

    Task &finally(std::function<void()> &&func) {
        handle.promise().on_completed([func](auto result) { func(); });
        return *this;
    }

    explicit Task(std::coroutine_handle<promise_type> handle) noexcept
        : handle(handle) {}

    Task(Task &&task) noexcept : handle(std::exchange(task.handle, {})) {}

    Task(Task &) = delete;

    Task &operator=(Task &) = delete;

    ~Task() {
        if (handle) handle.destroy();
    }

   private:
    std::coroutine_handle<promise_type> handle;
};

using InlineExecutor = NoopExecutor;
using DetachExecutor = NewThreadExecutor;
