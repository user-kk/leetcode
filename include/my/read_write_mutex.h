#pragma once
#include <common.h>
#include <condition_variable>
#include <cstddef>
#include <mutex>

class ReadWriteMutex {
   public:
    ReadWriteMutex() = default;
    ~ReadWriteMutex() = default;
    DISABLE_COPY_AND_MOVE(ReadWriteMutex);

    void lock() {
        cnt_.wait(0);
        m_.lock();
    }

    void lock_shared() {
        if (cnt_ == 0) {
            std::lock_guard g{lock_m_};

            if (cnt_ != 0) {
                cnt_++;
                return;
            }

            m_.lock();
            cnt_++;
            return;
        }
        cnt_++;
    }

    void unlock_shared() {
        if (--cnt_ == 0) {
            m_.unlock();
            cnt_.notify_one();
        }
    }

    void unlock() { m_.unlock(); }

   private:
    std::atomic<size_t> cnt_;
    std::mutex m_;
    std::mutex lock_m_;
};

class ReadWriteLock {
    std::condition_variable cv_;
    size_t reader_cnt_ = 0;
    bool writer = false;
    std::mutex m_;

    void read_lock() {
        std::unique_lock lock(m_);
        cv_.wait(lock, [this]() { return !writer; });
        reader_cnt_++;
    }

    void read_unlock() {
        std::unique_lock lock(m_);
        reader_cnt_--;
        if (reader_cnt_ == 0) {
            cv_.notify_all();
        }
    }

    void write_lock() {
        std::unique_lock lock(m_);
        cv_.wait(lock, [this]() { return !writer && reader_cnt_ == 0; });
        writer = true;
    }

    void write_unlock() {
        std::unique_lock lock(m_);
        writer = false;
        cv_.notify_all();
    }
};
