/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int rob(vector<int>& nums) {
        vector<int> r(nums.size());   // 偷
        vector<int> nr(nums.size());  // 不偷
        r[0] = nums[0];
        nr[0] = 0;
        for (int i = 1; i < nums.size(); i++) {
            r[i] = nums[i] + nr[i - 1];
            nr[i] = std::max(r[i - 1], nr[i - 1]);
        }
        return std::max(r[nums.size() - 1], nr[nums.size() - 1]);
    }
};
// @lc code=end
