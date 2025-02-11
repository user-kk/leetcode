#include "common.h"
#include <coroutine>
#include <stdexcept>
#include <fmt/core.h>

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
    Generater(Generater&& g) noexcept : handle(g.handle) { g.handle = {}; }
    Generater& operator=(Generater&& g) noexcept {
        handle.destroy();
        handle = g.handle;
        g.handle = {};
        return *this;
    }
    Generater(const Generater& g) = delete;
    Generater& operator=(const Generater& g) = delete;

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
Generater seq() {
    int i = 0;
    for (int i = 0; i < 3; i++) {
        // 也可以使用co_yield co_yield等价于co_await promise.yield_value(expr)
        co_await i++;
    }
}

MYTEST(1) {
    auto g = seq();

    if (g.has_next()) {
        fmt::println("{}", g.next());
    }
    auto g1 = std::move(g);
    if (g1.has_next()) {
        fmt::println("{}", g1.next());
    }
}