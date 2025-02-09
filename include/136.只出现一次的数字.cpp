/*
 * @lc app=leetcode.cn id=136 lang=cpp
 *
 * [136] 只出现一次的数字
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (int i : nums) {
            ret = ret ^ i;
        }
        return ret;
    }
};
// @lc code=end
