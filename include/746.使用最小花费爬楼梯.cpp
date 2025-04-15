/*
 * @lc app=leetcode.cn id=746 lang=cpp
 *
 * [746] 使用最小花费爬楼梯
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int minCostClimbingStairs(vector<int>& cost) {
        int a = cost[0];
        int b = cost[1];
        for (int i = 2; i < cost.size(); i++) {
            if (i % 2 == 0) {
                a = std::min(a, b) + cost[i];
            } else {
                b = std::min(a, b) + cost[i];
            }
        }

        return std::min(a, b);
    }
};
// @lc code=end
