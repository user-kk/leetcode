#include "common.h"
#include "./threadpool.hpp"
#include <csignal>
#include <fmt/core.h>

ThreadPool* g_pool;
void signal_handler(int signum) {
    if (signum == SIGINT) {
        fmt::print("SIGINT received\n");
        g_pool->stop();
        std::quick_exit(0);
    }
}

void this_thread_sleep_for(std::chrono::seconds s) {
    std::this_thread::sleep_for(s);
}
int kk() {
    std::this_thread::sleep_for(5s);
    return 1;
}

int main() {
    ThreadPool pool(5);
    g_pool = &pool;
    pool.add_task(this_thread_sleep_for, 200s);
    pool.add_task(this_thread_sleep_for, 40s);
    pool.add_task(this_thread_sleep_for, 70s);
    pool.add_task(this_thread_sleep_for, 100s);
    auto i = pool.add_task(kk);
    auto previous_handler = std::signal(SIGINT, signal_handler);
    if (previous_handler == SIG_ERR) {
        fmt::print("Error setting signal handler\n");
        return 1;
    }
    i.get();

    return 0;
}