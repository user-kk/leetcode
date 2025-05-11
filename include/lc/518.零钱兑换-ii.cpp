/*
 * @lc app=leetcode.cn id=518 lang=cpp
 *
 * [518] 零钱兑换 II
 */
#include <climits>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                //! 这题的测试用例贱，dp的中间结果可能大于int
                //! 但最终结果在int内，所以直接不去计算特别大的中间结果
                if (static_cast<long>(dp[i]) + dp[i - coin] < INT_MAX) {
                    dp[i] += dp[i - coin];
                }
            }
        }
        return dp[amount];
    }
};
// @lc code=end
