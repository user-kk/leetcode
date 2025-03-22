#include "common.h"
#include "./threadpool.hpp"
#include <csignal>
#include <cstdlib>
#include <functional>
#include <future>
#include <system_error>
#include <fmt/base.h>
#include <fmt/core.h>

namespace Signal {
std::function<void(int)> sigint_callback;
void signal_handler(int signum) {
    if (Signal::sigint_callback) {
        Signal::sigint_callback(signum);
    }
}

void register_signal_handle(std::function<void(int)>&& callback) {
    Signal::sigint_callback = std::move(callback);
    auto previous_handler = std::signal(SIGINT, Signal::signal_handler);
    if (previous_handler == SIG_ERR) {
        throw std::runtime_error("Error setting signal handler\n");
    }
}
};  // namespace Signal

void this_thread_sleep_for(std::chrono::seconds s) {
    std::this_thread::sleep_for(s);
}
int kk() {
    std::this_thread::sleep_for(5s);
    return 1;
}

int main() {
    ThreadPool pool(5);
    Signal::register_signal_handle([&pool](int signum) {
        if (signum == SIGINT) {
            fmt::println("bye!");
            pool.stop();
            std::quick_exit(0);
        }
    });
    pool.add_task(this_thread_sleep_for, 4s);
    pool.add_task(this_thread_sleep_for, 6s);
    pool.add_task(this_thread_sleep_for, 3s);
    pool.add_task(this_thread_sleep_for, 1s);
    auto i = pool.add_task(kk);

    int a = i.get();
    fmt::println("get i:{}", a);

    return 0;
}