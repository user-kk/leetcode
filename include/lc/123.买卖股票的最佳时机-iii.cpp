/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */
#include <array>
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! 自身有状态的，并且状态会对下一次的决策产生影响的，为dp数组多增加一层状态的维度
    int maxProfit(vector<int>& prices) {
        enum T {
            yes1 = 0,  // 持有，第一次
            yes2,      // 持有，第二次
            no_yes0,   // 不持有，没有持有过
            no_yes1,   // 不持有，持有过1次
            no_yes2    // 不持有，持有过2次
        };

        std::vector<std::array<int, 5>> dp(prices.size());
        dp[0][yes1] = -prices[0];  // 买一次
        dp[0][yes2] = -prices[0];  // 同一天内买两次，卖一次
        dp[0][no_yes0] = 0;
        dp[0][no_yes1] = 0;  // 同一天买卖一次
        dp[0][no_yes2] = 0;  // 同一天买卖两次

        for (int i = 1; i < prices.size(); i++) {
            dp[i][yes1] =
                std::max({dp[i - 1][yes1], dp[i - 1][no_yes0] - prices[i]});
            dp[i][yes2] =
                std::max({dp[i - 1][yes2], dp[i - 1][no_yes1] - prices[i]});
            dp[i][no_yes0] = dp[i - 1][no_yes0];
            dp[i][no_yes1] =
                std::max({dp[i - 1][yes1] + prices[i], dp[i - 1][no_yes1]});
            dp[i][no_yes2] =
                std::max({dp[i - 1][yes2] + prices[i], dp[i - 1][no_yes2]});
        }
        return *std::max_element(dp[prices.size() - 1].begin(),
                                 dp[prices.size() - 1].end());
    }
};
// @lc code=end
