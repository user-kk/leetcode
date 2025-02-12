#include <functional>
#include <future>
#include <type_traits>
#include <vector>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>

class ThreadPool {
   public:
    ThreadPool() = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    explicit ThreadPool(size_t n) {
        for (size_t i = 0; i <= n; i++) {
            threads_.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        has_task_.wait(lock, [this] {
                            return this->tasks_.empty() || this->stop_;
                        });
                        if (this->tasks_.empty()) {
                            return;
                        }
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    }
                    task();
                }
            });
        }
    }
    void stop() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (stop_) {
                return;
            }
            stop_ = true;
        }
        has_task_.notify_all();
        for (auto& t : threads_) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    template <typename F, typename... Args>
    auto add_task(F&& f, Args&&... args)
        -> std::future<std::result_of_t<F(Args...)>> {
        using return_type = std::result_of_t<F(Args...)>;
        auto task = std::packaged_task<return_type()>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto result = task.get_future();

        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (stop_) {
                throw std::runtime_error("add task on stopped thread pool");
            }
            tasks_.emplace([task_p = std::move(task)]() mutable { task_p(); });
        }
        has_task_.notify_one();
        return result;
    }

    ~ThreadPool() {
        for (auto& t : threads_) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

   private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::condition_variable has_task_;
    std::mutex mutex_;
    bool stop_ = false;
};