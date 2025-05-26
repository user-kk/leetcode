#pragma once

namespace My {
template <typename T>
struct DefaultDeleter {
    void operator()(T *p) { delete p; }
};

template <typename T>
struct DefaultDeleter<T[]> {
    void operator()(T *p) { delete[] p; }
};
}  // namespace My