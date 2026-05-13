#include "common.h"
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

class T {
   private:
    std::condition_variable not_empty;
    std::condition_variable not_full;
    std::mutex m;
    std::queue<int> q;
    int capacity;

   public:
    T(int n) : capacity(n) {}
    void produce(int n) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> l(m);
            not_full.wait(l, [this]() { return q.size() < this->capacity; });
            std::this_thread::sleep_for(1s);
            q.push(i);
            cout << "produce " << i << endl;
            not_empty.notify_one();
        }
    }

    void consume(int n) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> l(m);
            not_empty.wait(l, [this]() { return q.size() > 0; });
            std::this_thread::sleep_for(1s);
            cout << "consume " << q.front() << endl;
            q.pop();
            not_full.notify_one();
        }
    }
};

MYTEST(1) {
    T t(5);
    std::thread t1([&t]() { t.produce(10); });
    std::thread t2([&t]() { t.consume(10); });

    t1.join();
    t2.join();
}