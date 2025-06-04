#pragma once
#include <cstddef>
#include <cstring>

namespace My {
inline void memmove(void* dest, const void* src, size_t len) {
    const char* s = static_cast<const char*>(src);
    char* d = static_cast<char*>(dest);
    if (len == 0) {
        return;
    }
    if (s <= d) {
        for (size_t i = len; i != 0; i--) {
            d[i - 1] = s[i - 1];
        }
    } else {
        for (size_t i = 0; i < len; i++) {
            d[i] = s[i];
        }
    }
}
}  // namespace My