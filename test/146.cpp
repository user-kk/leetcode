#include <gtest/gtest.h>

#include <146.lru-缓存.cpp>
#include <unordered_map>

MYTEST(1) {
    LRUCache a(2);
    a.put(2, 1);
    a.put(2, 2);
    ASSERT_EQ(a.get(2), 2);
    a.put(1, 1);
    a.put(4, 1);
    ASSERT_EQ(a.get(2), -1);
}

MYTEST(2) {
    std::unordered_map<int, int> k;
    k.insert({1, 1});
    k.insert({1, 2});
    std::unordered_map<int, int> k2{{1, 2}};
    ASSERT_NE(k, k2);
}