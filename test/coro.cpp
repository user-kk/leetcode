#include "common.h"
#include <coroutine>
#include <stdexcept>
#include <thread>
#include <variant>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/std.h>
#include "coro.h"

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

Task<int, DetachExecutor> simple_task1() {
    std::variant<int, int> a;
    std::exception_ptr aa = nullptr;

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    co_return 1;
}

Task<int, DetachExecutor> simple_task2() {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(4s);
    fmt::println("thread_id:{},task2", std::this_thread::get_id());
    co_return 2;
}

Task<int> simple_task() {
    auto a = co_await simple_task1();
    auto b = co_await simple_task2();
    co_return a + b;
}

Task<int> simple_task_when_all() {
    auto [a, b] = co_await when_all(simple_task1(), simple_task2());
    co_return a + b;
}

Task<int> simple_task_when_any() {
    auto k = co_await when_any(simple_task1(), simple_task2());
    if (k.index() == 0) {
        co_return std::get<0>(k);
    } else {
        co_return std::get<1>(k);
    }
}

MYTEST(2) {
    auto t = simple_task();
    t.then([](int v) {
         fmt::println("{}", v);
     }).catching([](std::exception& e) { fmt::println("{}", e.what()); });

    try {
        t.get_result();
    } catch (std::exception& e) {
        fmt::println("{}", e.what());
    }
}

Task<int, DetachExecutor> simple_task3() {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    fmt::println("thread_id:{},task3", std::this_thread::get_id());
    co_return 2;
}

Task<int, InlineExecutor> f1() {
    fmt::println("thread_id:{},f1:1", std::this_thread::get_id());
    int a = co_await simple_task3();
    fmt::println("thread_id:{},f1:2", std::this_thread::get_id());
    co_return a + 1;
}

MYTEST(3) {
    fmt::println("thread_id:{},main", std::this_thread::get_id());
    auto t = f1();
    t.then([](int v) {
         fmt::println("thread_id:{},main2,v:{}", std::this_thread::get_id(), v);
     }).catching([](std::exception& e) { fmt::println("{}", e.what()); });
    try {
        t.get_result();
        fmt::println("thread_id:{},main3", std::this_thread::get_id());
    } catch (std::exception& e) {
        fmt::println("{}", e.what());
    }
    fmt::println("thread_id:{},main4", std::this_thread::get_id());
    this_thread::sleep_for(7s);
}

MYTEST(4) {
    auto t = simple_task_when_all();
    t.then([](int v) {
         fmt::println("{}", v);
     }).catching([](std::exception& e) { fmt::println("{}", e.what()); });

    try {
        t.get_result();
    } catch (std::exception& e) {
        fmt::println("{}", e.what());
    }
}

MYTEST(5) {
    auto t = simple_task_when_any();
    t.then([](int v) {
         fmt::println("{}", v);
     }).catching([](std::exception& e) { fmt::println("{}", e.what()); });

    try {
        t.get_result();
    } catch (std::exception& e) {
        fmt::println("{}", e.what());
    }
}