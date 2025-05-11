#include "common.h"

#include <fmt/core.h>
#include <fmt/std.h>
#include <coroutine>
#include <thread>
#include <iostream>

namespace {

struct Task {
    struct TaskPromise {
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }

        Task get_return_object() {
            return Task{
                std::coroutine_handle<TaskPromise>::from_promise(*this)};
        }
        void return_value(int v) { this->ret = v; }
        int ret = 0;
    };
    using promise_type = TaskPromise;

    explicit Task(std::coroutine_handle<TaskPromise> handle) noexcept
        : handle(handle) {}
    Task(Task &&other) noexcept : handle(std::exchange(other.handle, {})) {}
    ~Task() {
        if (handle) handle.destroy();
    }
    bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
        std::thread([handle]() {
            this_thread::sleep_for(1s);
            fmt::println("thread_id:{},resume_begin",
                         std::this_thread::get_id());
            handle.resume();
            fmt::println("thread_id:{},resume_end", std::this_thread::get_id());
        }).detach();
    }
    int await_resume() noexcept { return handle.promise().ret; }

    std::coroutine_handle<TaskPromise> handle;
};
}  // namespace

Task simple_task2() { co_return 2; }

Task simple_task() {
    fmt::println("thread_id:{},simple_task", std::this_thread::get_id());
    int a = co_await simple_task2();
    fmt::println("thread_id:{},simple_task_resume", std::this_thread::get_id());
    co_return 1;
}

MYTEST(1) {
    fmt::println("thread_id:{},main", std::this_thread::get_id());
    auto task = simple_task();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::coroutine_handle<> a;
    std::coroutine_handle<> b;
    a = b;
}
