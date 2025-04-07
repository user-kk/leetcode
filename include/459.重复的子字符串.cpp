/*
 * @lc app=leetcode.cn id=459 lang=cpp
 *
 * [459] 重复的子字符串
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    bool repeatedSubstringPattern(string s) {
        if (s.size() == 1) {
            return false;
        }
        // 得到next数组
        vector<int> next(s.size(), 0);

        for (int i = 1; i < s.size(); i++) {
            int cur = next[i - 1];
            while (cur != 0 && s[cur] != s[i]) {
                cur = next[cur - 1];
            }

            if (cur == 0) {
                next[i] = s[0] == s[i] ? 1 : 0;
            } else {
                next[i] = cur + 1;
            }
        }

        // 得到最长相同前后缀的长度，由于可能过长，所以选择2*len <= s.size的
        int len = next.back();

        while (2 * len > s.size()) {
            len = next[len - 1];
        }

        if (len == 0) {
            return false;
        }

        // 验证 例如 ababab  ,len=2 ,验证next[3]和next[5]的值是否都大于等于2
        for (int i = 2 * len - 1; i < s.size(); i = i + len) {
            if (next[i] < len) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end
