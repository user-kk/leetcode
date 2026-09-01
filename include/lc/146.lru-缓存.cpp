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
    struct KV {
        int k;
        int v;
    };

    LRUCache(int capacity) : capacity(capacity), size(0) {}

    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) {
            return -1;
        }

        KV kv = *(it->second);
        access.erase(it->second);
        //! unordered_map的insert函数当有key时插入会失败，而非直接覆盖
        //! 要覆盖可用insert_or_assign
        m[kv.k] = access.insert(access.end(), kv);
        return kv.v;
    }

    void put(int key, int value) {
        if (get(key) != -1) {
            m[key]->v = value;
            return;
        }
        // 容量不够，淘汰一个
        if (size >= capacity) {
            KV kv = access.front();
            access.pop_front();
            m.erase(kv.k);
            size--;
        }

        m[key] = access.insert(access.end(), {key, value});
        size++;
    }

    int capacity;
    int size;
    std::list<KV> access;
    std::unordered_map<int, std::list<KV>::iterator> m;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
