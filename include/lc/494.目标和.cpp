/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 */
#include <numeric>
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! a+b = sum;a-b =target; a = (sum+target)/2;
    //!  又因a,b都为大于等于零的整数，所以sum+target不能为负，不能为奇数
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        // 小于零或为奇数时不可能凑成

        if ((sum + target) < 0 || (sum + target) % 2 == 1) {
            return 0;
        }
        int t = (sum + target) / 2;
        vector<int> dp(t + 1, 0);
        // 只需要自己就可以凑成i的情况
        dp[0] = 1;

        for (int num : nums) {
            for (int i = t; i >= num; i--) {
                dp[i] += dp[i - num];
            }
        }
        return dp[t];
    }
};
// @lc code=end
