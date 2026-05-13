/*
 * @lc app=leetcode.cn id=318 lang=cpp
 *
 * [318] 最大单词长度乘积
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxProduct(vector<string>& words) {
        if (words.size() <= 1) {
            return 0;
        }
        struct T {
            size_t len;
            uint32_t hash;  // 相当于一个bitmap 存放26个字母
        };

        vector<T> k;
        k.reserve(words.size());
        for (const string& s : words) {
            uint32_t hash = 0;
            for (char c : s) {
                hash = hash | (1 << (c - 'a'));
            }
            k.push_back({s.size(), hash});
        }

        size_t ret = 0;
        for (int i = 0; i < k.size() - 1; i++) {
            for (int j = i + 1; j < k.size(); j++) {
                if ((k[i].hash & k[j].hash) == 0) {
                    ret = std::max(ret, k[i].len * k[j].len);
                }
            }
        }
        return ret;
    }
};
// @lc code=end
