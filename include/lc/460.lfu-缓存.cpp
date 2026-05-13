/*
 * @lc app=leetcode.cn id=460 lang=cpp
 *
 * [460] LFU 缓存
 */
#include "common.h"
// @lc code=start
class LFUCache {
   public:
    struct KV {
        int key;
        int value;
        int f;
    };
    LFUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = k2v.find(key);
        if (it == k2v.end()) {
            return -1;
        }

        // 找到

        auto [k, v, f] = *(it->second);

        KV new_kv = {k, v, f + 1};
        f2v[f].erase(it->second);
        auto new_it = f2v[f + 1].insert(f2v[f + 1].end(), new_kv);
        k2v[k] = new_it;
        if (f2v[minf].empty()) {
            //! 之前保证一定有值，如果突然没了，那么肯定是这次更新引起的
            minf = f + 1;
        }

        return v;
    }

    void put(int key, int value) {
        int v = get(key);
        if (v != -1) {  // 之前有，那容量不用更，一定够

            // 缓存中有，把新值置入，频率已经调整完
            k2v[key]->value = value;

            return;
        }

        if (n + 1 > cap) {
            // 容量不够淘汰一个

            // 淘汰
            auto it = f2v[minf].begin();
            k2v.erase(it->key);
            f2v[minf].erase(it);
            n--;
        }

        KV new_kv = {key, value, 1};
        auto new_it = f2v[1].insert(f2v[1].end(), new_kv);
        k2v[key] = new_it;
        //! 新插入的一定是最小频率，否则会触发上面的更新，而非插入
        //! 这个导致了维护minf 的开销是O(1)的
        minf = 1;
        n++;
    }

    int minf = 1;

    std::unordered_map<int, std::list<KV>> f2v;
    std::unordered_map<int, std::list<KV>::iterator> k2v;
    int cap;
    int n = 0;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
