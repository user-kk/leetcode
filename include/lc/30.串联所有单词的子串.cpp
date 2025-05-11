/*
 * @lc app=leetcode.cn id=30 lang=cpp
 *
 * [30] 串联所有单词的子串
 */
#include <string_view>
#include "common.h"
// @lc code=start
class Solution {
   public:
    struct T {
        std::unordered_map<string_view, int> m;
        int num = 0;
        std::vector<int> save_vals;

        void init(vector<string>& words) {
            for (auto& s : words) {
                if (auto it = m.find(s); it != m.end()) {
                    it->second++;
                } else {
                    m.insert({s, 1});
                }
            }
            save_vals.reserve(m.size());
            for (auto& [_, v] : m) {
                save_vals.push_back(v);
            }
            num = m.size();
        }
        void insert(string_view s) {
            if (auto it = m.find(s); it != m.end()) {
                it->second--;
                if (it->second == 0) {
                    num--;
                }
            }
        }
        void restore(string_view s) {
            if (auto it = m.find(s); it != m.end()) {
                it->second++;
                if (it->second == 1) {
                    num++;
                }
            }
        }
        bool success() const { return num == 0; }
        void clear() {
            int i = 0;
            for (auto& [_, v] : m) {
                v = save_vals[i];
                i++;
            }
            num = m.size();
        }
    };
    vector<int> findSubstring(string_view s, vector<string>& words) {
        T t;
        t.init(words);
        vector<int> ret;

        int k = words[0].size();

        for (int begin = 0; begin < k; begin++) {
            int left = begin;
            for (int i = begin; i < s.size(); i = i + k) {
                t.insert(s.substr(i, k));
                if (t.success()) {
                    while (t.success()) {
                        if (i + k - left == words.size() * k) {
                            ret.push_back(left);
                        }
                        t.restore(s.substr(left, k));
                        left = left + k;
                    }
                }
            }
            t.clear();
        }

        return ret;
    }
};
// @lc code=end
