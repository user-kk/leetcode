#include "common.h"
#include <fmt/base.h>
#include <fmt/core.h>
#include <asio.hpp>
#include <asio/read_until.hpp>
#include <asio/steady_timer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/use_awaitable.hpp>
#include <asio/awaitable.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/buffer.hpp>
#include <asio/write.hpp>
#include <asio/read.hpp>
#include <asio/as_tuple.hpp>
#include <variant>
#include "asio/experimental/awaitable_operators.hpp"
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