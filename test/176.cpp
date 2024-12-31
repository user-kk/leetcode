#include <fmt/color.h>
#include <fmt/core.h>
#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ios>
#include <iostream>
#include <limits>
#include <memory_resource>
#include <regex>
#include <sstream>
#include <system_error>

#include "167.两数之和-ii-输入有序数组.cpp"
MYTEST(1) {
    Solution s;
    std::vector<int> a{1, 1};
    std::vector<int> b{1, 1 + 1};
    ASSERT_EQ(s.twoSum(a, 2), b);
}

MYTEST(2) {
    std::ostringstream oss;
    oss << '[';
    std::vector<float> v{1.1, 2.295, 3.744};
    for (int i = 0; i < v.size(); i++) {
        if (i != v.size() - 1) {
            oss << std::round(v[i] * 100) / 100.0 << ',';
        } else {
            oss << std::round(v[i] * 100) / 100.0;
        }
    }
    oss << ']';

    auto result = oss.str();
    result.clear();
}

MYTEST(3) {
    std::string k = "178.5abc";
    stringstream deserialize_stream;
    deserialize_stream.clear();
    deserialize_stream.str(k);

    float float_value = 0;
    deserialize_stream >> float_value;
    std::cout << std::boolalpha << (bool)deserialize_stream
              << deserialize_stream.eof() << float_value << std::endl;
}

class MyAlloc {
   public:
    template <class T, class... Ts>
    T* get(Ts... ts) {
        T* ret = static_cast<T*>(pool.allocate(sizeof(T), alignof(T)));
        current_used_ =
            reinterpret_cast<std::byte*>(ret) + sizeof(T) - buf.data();
        ret = new (ret) T(ts...);
        return ret;
    }
    [[nodiscard]] int current_used() const { return current_used_; }

   private:
    std::array<std::byte, 2000> buf;
    std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
    int current_used_ = 0;
};

class A {
   public:
    explicit A(int i) : i_(i) {
        fmt::print(fmt::fg(fmt::color::red), "constuct\n");
    }

   private:
    int i_ = 0;
};

MYTEST(4) {
    MyAlloc alloc;
    int* a = alloc.get<int>();
    std::cout << alloc.current_used() << std::endl;
    double* b = alloc.get<double>();
    std::cout << alloc.current_used() << std::endl;

    A* kk = alloc.get<A>(1111);
    std::cout << alloc.current_used() << std::endl;
}

MYTEST(5) {
    constexpr int MAX_FLOATS = 100;
    const char* data =
        "[9.0,12.0,9.0,9.0,66.0,14.0,20.0,13.0,112.0,73.0,27.0,49.0,49.0,9.0,9."
        "0,13.0,103.0,33.0,2.0,0.0,0.0,0.0,5.0,12.0,2.0,0.0,0.0,0.0,0.0,1.0,3."
        "0,6.0,18.0,25.0,10.0,7.0,38.0,66.0,54.0,42.0,62.0,62.0,46.0,11.0,0.0,"
        "5.0,29.0,105.0,21.0,14.0,4.0,0.0,0.0,1.0,28.0,29.0,0.0,0.0,0.0,0.0,1."
        "0,7.0,18.0,17.0,36.0,3.0,0.0,1.0,41.0,126.0,42.0,54.0,126.0,12.0,0.0,"
        "0.0,10.0,51.0,31.0,126.0,12.0,0.0,0.0,0.0,12.0,80.0,126.0,46.0,0.0,0."
        "0,0.0,0.0,10.0,79.0,95.0,78.0,54.0,12.0,0.0,1.0,55.0,26.0,1.0,4.0,126."
        "0,46.0,0.0,0.0,32.0,99.0,37.0,22.0,4.0,0.0,0.0,0.0,46.0,123.0,83.0,21."
        "0,7.0,0.0,0.0,0.0,7.0,71.0,56.0,77.0]";
    int len = strlen(data);

    vector<float> array;
    array.reserve(128);
    auto start = std::chrono::high_resolution_clock::now();
    const char* ptr = data + 1;
    char* endPtr = nullptr;
    while (*ptr != ']') {
        // 使用strtof函数将字符串转换为浮点数
        array.push_back(strtof(ptr, &endPtr));

        // 检查是否成功转换
        if (endPtr == ptr) {
            ASSERT_TRUE(false);
        }

        ptr = endPtr;  // 移动指针到下一个数字

        // 检查是否到达数组末尾
        if (*ptr == ',') {
            ptr++;  // 跳过逗号
        }
    }
    // 结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算持续时间
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto aa = duration.count();
    std::cout << aa << endl;

    int ir = 1;
}