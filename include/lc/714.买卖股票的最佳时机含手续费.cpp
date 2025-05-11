/*
 * @lc app=leetcode.cn id=714 lang=cpp
 *
 * [714] 买卖股票的最佳时机含手续费
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxProfit(vector<int>& prices, int fee) {
        enum T { have, empty };
        array<int, 2> dp{};
        dp[have] = -prices[0] - fee;
        dp[empty] = 0;
        array<int, 2> dp_pre{};

        for (int i = 1; i < prices.size(); i++) {
            dp_pre = dp;
            dp[have] = std::max(dp_pre[have], dp[empty] - prices[i] - fee);
            dp[empty] = std::max(dp[empty], dp[have] + prices[i]);
        }

        return dp[empty];
    }
};
// @lc code=end
