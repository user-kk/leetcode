/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
 */

#include "common.h"
// @lc code=start
class Solution {
   public:
    int robInternal(span<int> nums) {
        if (nums.size() == 0) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return std::max(nums[0], nums[1]);
        }

        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = std::max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp.back();
    }
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return std::max(nums[0], nums[1]);
        }

        // 分别考虑两种选择，选nums[0]和不选nums[0]

        // 选nums[0],变成nums[2]->num[n-2]的版本
        int ret1 =
            robInternal(span<int>(nums.begin() + 2, nums.end() - 1)) + nums[0];

        // 不选nums[0],变成nums[1]->nums[n-1]版本
        int ret2 = robInternal(span<int>(nums.begin() + 1, nums.end()));
        return std::max(ret1, ret2);
    }
};
// @lc code=end
