/*
 * @lc app=leetcode.cn id=2716 lang=cpp
 *
 * [2716] 最小化字符串长度
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int minimizedStringLength(string s) {
        std::ranges::sort(s);
        auto it = std::unique(s.begin(), s.end());
        return it - s.begin();
    }
};
// @lc code=end
