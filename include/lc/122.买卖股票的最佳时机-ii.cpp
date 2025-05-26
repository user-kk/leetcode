/*
 * @lc app=leetcode.cn id=122 lang=cpp
 *
 * [122] 买卖股票的最佳时机 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxProfit2(vector<int>& prices) {
        if (prices.size() == 1) {
            return 0;
        }
        int i = 0;
        for (i = static_cast<int>(prices.size()) - 2; i >= 0; i--) {
            if (prices[i] < prices[i + 1]) {
                break;
            }
        }
        if (i == -1) {
            return 0;
        }
        int ret = 0;

        int max = prices[i + 1];
        int min = 0;
        while (i >= 0) {
            for (; i >= 0; i--) {
                if (prices[i] > prices[i + 1]) {
                    break;
                }
            }
            min = prices[i + 1];
            ret += max - min;
            if (i == -1) {
                return ret;
            }
            for (; i >= 0; i--) {
                if (prices[i] < prices[i + 1]) {
                    break;
                }
            }
            max = prices[i + 1];
            if (i == -1) {
                return ret;
            }
        }
        return 0;
    }

    int maxProfit(vector<int>& prices) {
        std::array<int, 2> dp = {0, -prices[0]};

        for (int i = 1; i < prices.size(); i++) {
            std::array<int, 2> pre = dp;
            dp[0] = std::max(pre[0], pre[1] + prices[i]);
            dp[1] = std::max(pre[1], pre[0] - prices[i]);
        }
        return std::max(dp[0], dp[1]);
    }
};
// @lc code=end
