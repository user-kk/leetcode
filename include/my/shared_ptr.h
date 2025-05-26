#pragma once

#include <functional>
#include <mutex>
#include "default_deleter.h"

namespace My {

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
   public:
    friend WeakPtr<T>;
    SharedPtr() : p_(nullptr), counter_(nullptr) {};
    explicit SharedPtr(T *p,
                       std::function<void(T *)> deleter = DefaultDeleter<T>{})
        : p_(p), counter_(p_ ? new Counter(p_, deleter) : nullptr) {
        counter_->add_share();
    }

    ~SharedPtr() {
        if (counter_) {
            counter_->release_share();
        }
        p_ = nullptr;
        counter_ = nullptr;
    }

    SharedPtr(const SharedPtr &other) : p_(other.p_), counter_(other.counter_) {
        if (counter_) {
            counter_->add_share();
        }
    }

    SharedPtr &operator=(const SharedPtr &other) {
        if (&other == this) [[unlikely]] {
            return *this;
        }

        if (counter_) {
            this->counter_->release_share();
        }

        this->p_ = other.p_;
        this->counter_ = other.counter_;

        if (counter_) {
            this->counter_->add_share();
        }

        return *this;
    }

    SharedPtr(SharedPtr &&other) noexcept
        : p_(other.p_), counter_(other.counter_) {
        other.p_ = nullptr;
        other.counter_ = nullptr;
    }

    SharedPtr &operator=(SharedPtr &&other) noexcept {
        if (&other == this) [[unlikely]] {
            return *this;
        }

        if (counter_) {
            this->counter_->release_share();
        }

        p_ = other.p_;
        counter_ = other.counter_;
        other.p_ = nullptr;
        other.counter_ = nullptr;

        return *this;
    }

    explicit operator bool() const { return p_ != nullptr; }
    T *get() { return p_; }
    T &operator*() { return *p_; }
    T *operator->() { return p_; }

    void reset(T *p = nullptr,
               std::function<void(T *)> deleter = DefaultDeleter<T>{}) {
        if (counter_) {
            counter_->release_share();
        }
        p_ = nullptr;
        counter_ = nullptr;

        p_ = p;
        if (p_) {
            counter_ = new Counter(p_, deleter);
            counter_->add_share();
        }
    }
    size_t use_count() { return counter_ ? counter_->use_count() : 0; }

   private:
    class Counter {
       public:
        explicit Counter(T *p, std::function<void(T *)> deleter)
            : p_(p), deleter_(deleter) {}
        void add_share() {
            std::lock_guard g{m_};
            share_count_++;
        }
        void add_weak() {
            std::lock_guard g{m_};
            weak_count_++;
        }
        void release_share() {
            std::lock_guard g{m_};
            if (--share_count_ != 0) {
                return;
            }
            // 到这里，share_count一定是为0的
            if (p_) {
                deleter_(p_);
            }

            if (weak_count_ == 0) {
                delete this;
            }
        }

        void release_weak() {
            std::lock_guard g{m_};
            if (--weak_count_ != 0) {
                return;
            }
            // weak_count == 0时，检测shared还有没有人用
            if (share_count_ == 0) {
                delete this;
            }
        }
        size_t use_count() {
            std::lock_guard g{m_};
            return share_count_;
        }

        bool try_add_share() {
            std::lock_guard g{m_};
            if (share_count_ == 0) {
                return false;
            }
            share_count_++;
            return true;
        }

       private:
        T *p_;
        std::mutex m_;
        size_t share_count_ = 0;
        size_t weak_count_ = 0;
        std::function<void(T *)> deleter_;
    };

    SharedPtr(T *p, Counter *counter) : p_(p), counter_(counter) {}
    T *p_;
    Counter *counter_;
};

template <typename T>
class WeakPtr {
   public:
    WeakPtr() : p_(nullptr), counter_(nullptr) {}
    explicit WeakPtr(const SharedPtr<T> &p) : p_(p.p_), counter_(p.counter_) {
        if (counter_) {
            counter_->add_weak();
        }
    }
    ~WeakPtr() {
        if (counter_) {
            counter_->release_weak();
        }
        p_ = nullptr;
        counter_ = nullptr;
    }

    WeakPtr(const WeakPtr &other) : p_(other.p_), counter_(other.counter_) {
        if (counter_) {
            counter_->add_weak();
        }
    }

    WeakPtr &operator=(const WeakPtr &other) {
        if (&other == this) [[unlikely]] {
            return *this;
        }

        if (counter_) {
            this->counter_->release_weak();
        }

        this->p_ = other.p_;
        this->counter_ = other.counter_;

        if (counter_) {
            this->counter_->add_weak();
        }

        return *this;
    }

    WeakPtr(WeakPtr &&other) noexcept : p_(other.p_), counter_(other.counter_) {
        other.p_ = nullptr;
        other.counter_ = nullptr;
    }

    WeakPtr &operator=(WeakPtr &&other) noexcept {
        if (&other == this) [[unlikely]] {
            return *this;
        }

        if (counter_) {
            this->counter_->release_weak();
        }

        p_ = other.p_;
        counter_ = other.counter_;
        other.p_ = nullptr;
        other.counter_ = nullptr;

        return *this;
    }
    SharedPtr<T> lock() const {
        if (p_ && counter_) {
            if (counter_->try_add_share()) {
                return SharedPtr(p_, counter_);
            }
        }
        return SharedPtr<T>();
    }

    std::size_t use_count() const {
        return counter_ ? counter_->use_count() : 0;
    }

   private:
    T *p_;
    SharedPtr<T>::Counter *counter_;
};
}  // namespace My