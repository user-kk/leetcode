#pragma once
#include <spdlog/spdlog.h>
#include <cassert>
#include <cstddef>
#include <list>
#include <memory>
#include <memory_resource>
#include <atomic>
#include <new>
#include <utility>

namespace My {

class MonotonicBufferResource : public std::pmr::memory_resource {
   public:
    // 要求一个block的大小远大于每次要申请的空间
    explicit MonotonicBufferResource(size_t init_block_size = 1024) noexcept
        : block_size_(init_block_size), cur_(0), deleter(this) {
        blocks_.emplace_back(block_size_, alignof(std::max_align_t));
    }
    struct Deleter {
        explicit Deleter(MonotonicBufferResource* res) : outer(res) {}
        MonotonicBufferResource* outer;
        template <typename T>
        void operator()(T* p) {
            outer->deconstruct(p);
        }
    };

    template <class T, class... Ts>
    T* new_as_row_ptr(Ts... ts) {
        T* ret = static_cast<T*>(do_allocate(sizeof(T), alignof(T)));
        ret = new (ret) T(ts...);
        return ret;
    }

    template <class T, class... Ts>
    std::unique_ptr<T, Deleter> new_as(Ts... ts) {
        T* ret = static_cast<T*>(do_allocate(sizeof(T), alignof(T)));
        ret = new (ret) T(ts...);
        return std::unique_ptr<T, Deleter>(ret, deleter);
    }

    template <class T>
    void deconstruct(T* p) {
        p->~T();
    }

   private:
    void* do_allocate(size_t bytes, size_t alignment) override {
        if (bytes > block_size_) {
            throw std::bad_alloc();
        }
        SPDLOG_DEBUG("alloc len:{} align:{}", bytes, alignment);

        size_t ptr = reinterpret_cast<size_t>(get_cur_ptr());

        size_t padding =
            ptr % alignment == 0 ? 0 : alignment - (ptr % alignment);

        if (cur_ + padding + bytes <= block_size_) {
            assert((ptr + padding) % alignment == 0);
            void* ret = get_cur_ptr() + padding;
            cur_ += (padding + bytes);
            return ret;
        }

        // 当前块剩余空间大小不够了，申请新块
        if (alignment <= alignof(std::max_align_t)) {
            blocks_.emplace_back(block_size_, alignof(std::max_align_t));
        } else {
            blocks_.emplace_back(block_size_, alignment);
        }
        cur_ = 0;
        void* ret = get_cur_ptr();
        cur_ += bytes;
        return ret;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {}

    bool do_is_equal(
        const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

    std::byte* get_cur_ptr() {
        return reinterpret_cast<std::byte*>(blocks_.back().get()) + cur_;
    }

    class Block {
       public:
        explicit Block(size_t bytes,
                       size_t alignment = alignof(std::max_align_t))
            : p_(std::aligned_alloc(alignment, bytes)) {}

        ~Block() {
            // NOLINTBEGIN(cppcoreguidelines-no-malloc)
            std::free(p_);
            // NOLINTEND(cppcoreguidelines-no-malloc)
        }

        Block(const Block&) = delete;
        Block& operator=(const Block&) = delete;
        Block(Block&& other) noexcept : p_(std::exchange(other.p_, nullptr)) {}
        Block& operator=(Block&& other) noexcept {
            // NOLINTBEGIN(cppcoreguidelines-no-malloc)
            std::free(p_);
            // NOLINTEND(cppcoreguidelines-no-malloc)
            p_ = std::exchange(other.p_, nullptr);
            return *this;
        }

        void* get() { return p_; }

       private:
        void* p_;
    };

    Deleter deleter;
    size_t cur_;
    size_t block_size_;

    std::list<Block> blocks_;
};

}  // namespace My