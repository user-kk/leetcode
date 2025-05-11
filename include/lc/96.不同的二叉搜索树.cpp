/*
 * @lc app=leetcode.cn id=96 lang=cpp
 *
 * [96] 不同的二叉搜索树
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 中序先序确定一棵树，中序一定，只需要考虑先序
    int numTrees(int n) {
        vector<int> dp(n + 1, 1);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            int sum = 0;
            for (int j = 1; j <= i; j++) {
                sum += dp[j - 1] * dp[i - j];
            }
            dp[i] = sum;
        }
        return dp[n];
    }
};
// @lc code=end
