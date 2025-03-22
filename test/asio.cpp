#include "common.h"
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/std.h>
#include <asio.hpp>
#include <asio/associated_allocator.hpp>
#include <asio/async_result.hpp>
#include <asio/read_until.hpp>
#include <asio/steady_timer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/use_awaitable.hpp>
#include <asio/awaitable.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/buffer.hpp>
#include <asio/use_future.hpp>
#include <asio/write.hpp>
#include <asio/read.hpp>
#include <asio/as_tuple.hpp>
#include <exception>
#include <stdexcept>
#include <system_error>
#include <thread>
#include <variant>
#include <asio/experimental/awaitable_operators.hpp>
using namespace asio;
using namespace asio::ip;

using default_token = as_tuple_t<use_awaitable_t<>>;

asio::awaitable<void> timer_coroutine(asio::steady_timer& t, int& count) {
    while (count <= 3) {
        co_await t.async_wait(asio::use_awaitable);
        fmt::println("count:{}", ++count);
        t.expires_after(std::chrono::seconds(2));
    }
}

MYTEST(1) {
    fmt::println("asio");
    asio::io_context io;
    asio::steady_timer t(io, std::chrono::seconds(2));
    int count = 0;

    asio::co_spawn(io, timer_coroutine(t, count), asio::detached);

    io.run();
    fmt::println("end");
}

struct Session : std::enable_shared_from_this<Session> {
    tcp::socket socket_;
    std::string buffer_;
    asio::io_context& io_context_;
    asio::steady_timer timer_;
    Session(tcp::socket&& socket, asio::io_context& io_context)
        : socket_(std::move(socket)),
          io_context_(io_context),
          timer_(steady_timer{io_context_}) {}

    void do_read() {
        auto p = this->shared_from_this();
        timer_.expires_after(5s);
        timer_.async_wait([p, this](std::error_code ec) {
            //! 要根据ec判断是否被取消了，如果被取消了，这个回调还是会被调用的
            if (!ec) {
                fmt::println("time out");
                socket_.shutdown(tcp::socket::shutdown_both);
                socket_.close();
            }
        });

        asio::async_read_until(
            socket_, asio::dynamic_buffer(buffer_), "\n",
            [p, this](std::error_code ec, std::size_t len) {
                if (!ec) {
                    timer_.cancel();
                    auto content = std::string_view{buffer_.data(), len};
                    fmt::println("content:{{{}}}", content);
                    if (content == "exit\n") {
                        socket_.shutdown(tcp::socket::shutdown_both);
                        socket_.close();
                        return;
                    }
                    do_write(len);
                }
            });
    }

    void do_write(size_t len) {
        auto p = this->shared_from_this();
        asio::async_write(socket_, asio::buffer(buffer_, len),
                          [p, this](std::error_code ec, std::size_t len) {
                              if (!ec) {
                                  buffer_.clear();
                                  do_read();
                              }
                          });
    }
};

MYTEST(2) {
    asio::io_context io;
    tcp::acceptor acceptor(io,
                           asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 9999));

    std::function<void(asio::error_code ec, tcp::socket socket)> handle =
        [&acceptor, &handle, &io](asio::error_code ec, tcp::socket socket) {
            if (!ec) {
                fmt::println("accept");
                std::make_shared<Session>(std::move(socket), io)->do_read();
                acceptor.async_accept(handle);
            }
        };

    acceptor.async_accept(handle);

    io.run();
}

asio::awaitable<void> echo(tcp::socket socket) {
    std::string buffer;
    while (true) {
        using namespace asio::experimental::awaitable_operators;
        using namespace asio::buffer_literals;
        asio::steady_timer t(co_await this_coro::executor, 5s);
        std::variant<std::monostate, size_t> result =
            co_await (t.async_wait(use_awaitable) ||
                      asio::async_read_until(socket, dynamic_buffer(buffer),
                                             "\n", use_awaitable));
        if (result.index() == 0) {
            fmt::println("time out");
            co_await asio::async_write(socket, "time_out"_buf);
            co_return;
        }
        if (buffer == "quit\n") {
            co_await asio::async_write(socket, "bye"_buf);
            co_return;
        }
        co_await asio::async_write(socket, dynamic_buffer(buffer));
        buffer.clear();
    }
}

asio::awaitable<void> echo2(tcp::socket socket) {
    std::string buffer;
    while (true) {
        using namespace asio::experimental::awaitable_operators;
        using namespace asio::buffer_literals;
        asio::steady_timer t(co_await this_coro::executor, 5s);
        std::variant<std::monostate, std::tuple<std::error_code, size_t>>
            result = co_await (
                t.async_wait(use_awaitable) ||
                asio::async_read_until(socket, dynamic_buffer(buffer), "\n",
                                       as_tuple(use_awaitable)));
        if (result.index() == 0) {
            fmt::println("time out");
            co_await asio::async_write(socket, "time_out"_buf);
            co_return;
        }
        if (buffer == "quit\n") {
            co_await asio::async_write(socket, "bye"_buf);
            co_return;
        }
        co_await asio::async_write(socket, dynamic_buffer(buffer));
        buffer.clear();
    }
}

asio::awaitable<void> listen() {
    auto executor = co_await this_coro::executor;
    tcp::acceptor acceptor(executor, tcp::endpoint(tcp::v4(), 9999));

    while (true) {
        auto socket = co_await acceptor.async_accept(executor);
        asio::co_spawn(executor, echo(std::move(socket)), asio::detached);
    }
}

MYTEST(3) {
    asio::io_context io;
    asio::co_spawn(io, listen(), asio::detached);
    io.run();
}

struct MyThreadPool {
    std::vector<std::thread> threads;
    asio::io_context io_thread_ctx;
    asio::io_context work_thread_ctx;
    static MyThreadPool& this_thread_pool() {
        static MyThreadPool pool;
        return pool;
    }
    ~MyThreadPool() {
        for (auto& i : threads) {
            if (i.joinable()) {
                i.join();
            }
        }
    }

   private:
    MyThreadPool() {
        threads.emplace_back([this]() {
            auto guard = asio::make_work_guard(io_thread_ctx);
            io_thread_ctx.run();
        });
        threads.emplace_back([this]() {
            auto guard = asio::make_work_guard(work_thread_ctx);
            work_thread_ctx.run();
        });
    }
};

asio::awaitable<int> kk2() {
    fmt::println("kk2: id1:{}", std::this_thread::get_id());
    asio::steady_timer t(co_await this_coro::executor, 5s);
    co_await t.async_wait(use_awaitable);
    fmt::println("kk2: id2:{}", std::this_thread::get_id());
    throw std::runtime_error("kk2 error");
    co_return 1;
}

asio::awaitable<void> kk1() {
    fmt::println("kk1: id1:{}", std::this_thread::get_id());
    int a = 0;
    try {
        a = co_await asio::co_spawn(
            MyThreadPool::this_thread_pool().work_thread_ctx, kk2,
            use_awaitable);  // 用use_awaitable会传播异常
    } catch (std::exception& e) {
        fmt::println("{}", e.what());
    }

    fmt::println("kk1: id2:{} a:{}", std::this_thread::get_id(), a);
    throw std::runtime_error("kk1 error");
}
asio::awaitable<void> kk3() {
    fmt::println("kk3: id1:{}", std::this_thread::get_id());
    co_return;
}

MYTEST(4) {
    fmt::println("main: id1:{}", std::this_thread::get_id());
    asio::co_spawn(MyThreadPool::this_thread_pool().io_thread_ctx, kk1(),
                   asio::detached);  // 用detach不会传播异常
    asio::co_spawn(MyThreadPool::this_thread_pool().io_thread_ctx, kk3(),
                   asio::detached);
    fmt::println("main: id2:{}", std::this_thread::get_id());
}

template <typename Token>
auto async_task(Token&& token) {
    return asio::async_initiate<Token, void(std::string, std::error_code)>(
        [](auto handle) {
            std::thread{
                [h = std::move(
                     handle)]() mutable {  // 必须加mutable，否则编译器报奇怪的错
                    fmt::println("async_task: id1:{}",
                                 std::this_thread::get_id());
                    this_thread::sleep_for(3s);
                    auto ex = asio::get_associated_executor(h);
                    std::string ret = "ret1111";
                    std::error_code rc;

                    ex.execute(
                        [h = std::move(h), ret, rc]() mutable { h(ret, rc); });
                }}
                .detach();
        },
        token);
}

asio::awaitable<void> async_task1() {
    fmt::println("async_task1: id1:{}", std::this_thread::get_id());

    auto [s, rc] = co_await async_task(as_tuple(use_awaitable));
    fmt::println("async_task1: id2:{},ret:{}", std::this_thread::get_id(), s);
    co_return;
}

asio::awaitable<void> async_task2() {
    fmt::println("async_task2: id1:{}", std::this_thread::get_id());
    co_return;
}

MYTEST(5) {
    fmt::println("main: id1:{}", std::this_thread::get_id());
    asio::io_context io;
    asio::co_spawn(io, async_task1(), asio::detached);
    asio::co_spawn(io, async_task2(), asio::detached);
    io.run();
    fmt::println("main: id2:{}", std::this_thread::get_id());
}