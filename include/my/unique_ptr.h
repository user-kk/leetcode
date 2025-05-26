#pragma once
#include "default_deleter.h"

namespace My {

template <typename T, typename D = DefaultDeleter<T>>
class UniquePtr {
   public:
    UniquePtr() : p_(nullptr) {}
    explicit UniquePtr(T *p) : p_(p) {}
    UniquePtr(UniquePtr &&other) noexcept : p_(other.p_) { other.p_ = nullptr; }
    ~UniquePtr() { destroy(); }
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;
    UniquePtr &operator=(UniquePtr &&other) noexcept {
        if (&other == this) {
            return *this;
        }
        p_ = other.p_;
        other.p_ = nullptr;
    };
    explicit operator bool() const { return p_ != nullptr; }
    T *get() { return p_; }
    T &operator*() { return *p_; }
    T *operator->() { return p_; }
    auto operator<=>(const UniquePtr &other) const {
        return this->p_ <=> other.p_;
    }
    void reset(T *p = nullptr) {
        destroy();
        p_ = p;
    }
    [[nodiscard]] T *release() {
        auto tmp = p_;
        p_ = nullptr;
        return tmp;
    }

   private:
    T *p_;

    void destroy() {
        if (p_) {
            D{}(p_);
            p_ = nullptr;
        }
    }
};
template <typename T, typename D>
class UniquePtr<T[], D> {
   public:
    explicit UniquePtr(T *p) : p_(p) {}
    UniquePtr(UniquePtr &&other) noexcept : p_(other.p_) { other.p_ = nullptr; }
    ~UniquePtr() { destory(); }
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;
    UniquePtr &operator=(UniquePtr &&other) noexcept {
        if (&other == this) {
            return *this;
        }
        p_ = other.p_;
        other.p_ = nullptr;
    };
    explicit operator bool() { return p_ != nullptr; }
    T *get() { return p_; }
    T &operator*() { return *p_; }
    T *operator->() { return p_; }
    bool operator!() const { return p_ == nullptr; }
    void reset(T *p = nullptr) {
        destory();
        p_ = p;
    }
    [[nodiscard]] T *release() {
        auto tmp = p_;
        p_ = nullptr;
        return tmp;
    }

   private:
    T *p_;

    void destory() {
        if (p_) {
            D{}(p_);
            p_ = nullptr;
        }
    }
};
}  // namespace My
