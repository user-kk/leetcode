/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        int dp = nums[0];
        int ret = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp = std::max(nums[i], nums[i] + dp);
            ret = std::max(ret, dp);
        }
        return ret;
    }
};
// @lc code=end
