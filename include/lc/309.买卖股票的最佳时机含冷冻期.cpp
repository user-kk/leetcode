/*
 * @lc app=leetcode.cn id=309 lang=cpp
 *
 * [309] 买卖股票的最佳时机含冷冻期
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        enum T { normal, buy, sold, cold };
        array<int, 4> dp{};
        dp[normal] = 0;
        dp[buy] = -prices[0];
        dp[sold] = 0;
        dp[cold] = 0;
        array<int, 4> dp_pre{};
        for (int i = 1; i < prices.size(); i++) {
            dp_pre = dp;
            dp[normal] = std::max(dp_pre[normal], dp_pre[cold]);
            dp[buy] = std::max({dp_pre[buy], dp_pre[cold] - prices[i],
                                dp_pre[normal] - prices[i]});
            dp[sold] = dp_pre[buy] + prices[i];
            dp[cold] = dp_pre[sold];
        }
        return *std::max_element(dp.begin(), dp.end());
    }
};
// @lc code=end
