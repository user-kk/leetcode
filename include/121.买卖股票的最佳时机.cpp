/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int max_v = 0;  // 右侧最大的价格
        int ret = 0;
        for (int i = prices.size() - 1; i >= 0; i--) {
            ret = std::max(ret, max_v - prices[i]);
            max_v = std::max(max_v, prices[i]);
        }
        return ret;
    }
};
// @lc code=end
