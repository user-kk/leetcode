/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */
#include "common.h"

#include <cstdarg>
#include <list>
// @lc code=start
class LRUCache {
   public:
    LRUCache(int capacity) : _capacity(capacity) {}

    int get(int key) {
        auto it = values.find(key);
        if (it == values.end()) {
            return -1;
        } else {
            access.erase(values[key].it);
            E e = it->second;
            values[key] = {e.v, access.insert(access.end(), key)};

            return e.v;
        }
    }

    void put(int key, int value) {
        auto it = values.find(key);
        if (it != values.end()) {
            E e = it->second;
            access.erase(e.it);
            values[key] = {value, access.insert(access.end(), key)};
            return;
        }
        // 没有时
        _use++;
        if (_use > _capacity) {
            auto dump = access.begin();
            values.erase(*dump);
            access.erase(dump);
            _use--;
        }

        values[key] = {value, access.insert(access.end(), key)};
    }
    struct E {
        int v;
        std::list<int>::iterator it;
    };
    std::unordered_map<int, E> values;
    std::list<int> access;
    int _capacity;
    int _use = 0;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
