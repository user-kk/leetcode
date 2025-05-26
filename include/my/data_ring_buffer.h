#pragma once

#include <unistd.h>
#include <cstddef>
#include <cstring>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace My {

class DataRingBuffer {
   public:
    explicit DataRingBuffer(size_t init_capacity = 1023)
        : m_buffer(init_capacity + 1) {}

    bool empty() const { return m_head == m_tail; }
    bool full() const { return m_head == (m_tail + 1) % m_buffer.size(); }
    size_t current_capacity() const { return m_buffer.size() - 1; }
    size_t size() const {
        return m_tail >= m_head ? m_tail - m_head
                                : m_buffer.size() - m_head + m_tail;
    }

    void reserve(size_t capacity) {
        capacity += 1;  // 补充上那个不能用的字节
        if (capacity <= current_capacity()) {
            return;
        }
        std::vector<std::byte> tmp(capacity);
        size_t pre_size = size();
        read_data_from_buffer(tmp.data(), pre_size);
        m_buffer.swap(tmp);
        m_head = 0;
        m_tail = pre_size;
    }

    std::optional<std::string> read_as_string(size_t len) {
        if (size() < len) {
            return std::nullopt;
        }
        std::string ret;
        ret.resize(len);

        read_data_from_buffer(ret.data(), len);

        return ret;
    }

    std::optional<std::string> read_all_as_string() {
        return read_as_string(size());
    }

    template <typename T>
    std::optional<T> read_as() {
        if (size() < sizeof(T)) {
            return std::nullopt;
        }
        T ret;
        read_data_from_buffer(&ret, sizeof(T));
        return ret;
    }

    // 尝试读数据，读完数据不改索引
    template <typename T>
    std::optional<T> peek_as() {
        if (size() < sizeof(T)) {
            return std::nullopt;
        }
        T ret;
        peek_data_from_buffer(&ret, sizeof(T));
        return ret;
    }

    bool peek_data_from_buffer(void *dest, size_t len) {
        if (len == 0) {
            return true;
        }

        if (size() < len) {
            return false;
        }

        if (m_head < m_tail) {
            memcpy(dest, m_buffer.data() + m_head, len);
            return true;
        }

        if (m_head + len <= m_buffer.size()) {
            memcpy(dest, m_buffer.data() + m_head, len);
            return true;
        }

        memcpy(dest, m_buffer.data() + m_head, m_buffer.size() - m_head);

        memcpy(static_cast<std::byte *>(dest) + m_buffer.size() - m_head,
               m_buffer.data(), len - (m_buffer.size() - m_head));
        return true;
    }

    // 返回是否成功
    bool read_data_from_buffer(void *dest, size_t len) {
        if (len == 0) {
            return true;
        }

        if (size() < len) {
            return false;
        }

        if (m_head < m_tail) {
            memcpy(dest, m_buffer.data() + m_head, len);
            m_head = (m_head + len) % m_buffer.size();
            return true;
        }

        if (m_head + len <= m_buffer.size()) {
            memcpy(dest, m_buffer.data() + m_head, len);
            m_head = (m_head + len) % m_buffer.size();
            return true;
        }

        memcpy(dest, m_buffer.data() + m_head, m_buffer.size() - m_head);

        memcpy(static_cast<std::byte *>(dest) + m_buffer.size() - m_head,
               m_buffer.data(), len - (m_buffer.size() - m_head));
        m_head = len - (m_buffer.size() - m_head);
        return true;
    }

    template <typename T>
    bool write_pod_into_buffer(const T &v) {
        return write_data_into_buffer(&v, sizeof(v));
    }

    bool write_string_into_buffer(std::string_view s) {
        return write_data_into_buffer(s.data(), s.size());
    }

    bool write_data_into_buffer(const void *src, size_t len) {
        if (len == 0) {
            return true;
        }

        if (current_capacity() - size() < len) {
            return false;
        }

        if (m_tail < m_head) {
            memcpy(m_buffer.data() + m_tail, src, len);
            m_tail = (m_tail + len) % m_buffer.size();
            return true;
        }

        if (m_tail + len <= m_buffer.size()) {
            memcpy(m_buffer.data() + m_tail, src, len);
            m_tail = (m_tail + len) % m_buffer.size();
            return true;
        }

        memcpy(m_buffer.data() + m_tail, src, m_buffer.size() - m_tail);

        memcpy(m_buffer.data(),
               static_cast<const std::byte *>(src) + (m_buffer.size() - m_tail),
               len - (m_buffer.size() - m_tail));
        m_tail = len - (m_buffer.size() - m_tail);
        return true;
    }

    // 默认扩容两倍
    void expand(size_t factor = 2) {
        size_t new_capacity = (m_buffer.size() - 1) * factor;
        reserve(new_capacity);
    }

   private:
    ssize_t write_buffer_from_fd(int fd) {
        if (full()) {
            throw std::runtime_error("buffer is full");
        }

        if (m_head <= m_tail) {
            //! 重点
            size_t can_write_len = m_head == 0 ? m_buffer.size() - m_tail - 1
                                               : m_buffer.size() - m_tail;

            ssize_t n = ::read(fd, m_buffer.data() + m_tail, can_write_len);
            if (n < 0) {
                return n;
            }
            m_tail = (m_tail + n) % m_buffer.size();
            return n;
        }

        ssize_t n = ::read(fd, m_buffer.data() + m_tail, m_head - m_tail - 1);
        if (n < 0) {
            return n;
        }
        m_tail = (m_tail + n) % m_buffer.size();
        return n;
    }
    ssize_t read_buffer_into_fd(int fd) {
        if (empty()) {
            throw std::runtime_error("buffer is empty");
        }

        if (m_tail < m_head) {
            ssize_t n =
                ::write(fd, m_buffer.data() + m_head, m_buffer.size() - m_head);
            if (n < 0) {
                return n;
            }
            m_head = (m_head + n) % m_buffer.size();
            return n;
        }
        ssize_t n = ::write(fd, m_buffer.data() + m_head, m_tail - m_head);
        if (n < 0) {
            return n;
        }
        m_head = (m_head + n) % m_buffer.size();
        return n;
    }

    std::vector<std::byte> m_buffer;
    size_t m_head{0};
    size_t m_tail{0};
};

}  // namespace My