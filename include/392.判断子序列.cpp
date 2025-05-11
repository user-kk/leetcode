/*
 * @lc app=leetcode.cn id=392 lang=cpp
 *
 * [392] 判断子序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    bool isSubsequence(string_view s, string_view t) {
        int cur = 0;
        if (cur == s.size()) {
            return true;
        }
        for (int i = 0; i < t.size(); i++) {
            if (t[i] == s[cur]) {
                cur++;
                if (cur == s.size()) {
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end
