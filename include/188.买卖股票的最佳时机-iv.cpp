/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxProfit(int k, vector<int>& prices) {
        std::vector<std::vector<int>> dp(prices.size(),
                                         std::vector<int>(2 * k + 1, 0));
        for (int i = 0; i < k; i++) {
            dp[0][i] = -prices[0];
        }
        dp[0][k] = 0;

        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < k; j++) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j + k] - prices[i]);
            }
            for (int j = k + 1; j < 2 * k + 1; j++) {
                dp[i][j] =
                    std::max(dp[i - 1][j], dp[i - 1][j - k - 1] + prices[i]);
            }
        }

        return *std::max_element(dp[prices.size() - 1].begin(),
                                 dp[prices.size() - 1].end());
    }
};
// @lc code=end
