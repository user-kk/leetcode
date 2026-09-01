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
        // dp[i]代表i个节点能组合成多少棵树
        // dp[i] = sum(dp[左孩子节点个数]*dp[右孩子节点个数])
        vector<int> dp(n + 1, 1);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {  // 枚举当前节点数
            int sum = 0;
            for (int j = 0; j <= i - 1; j++) {  // 枚举左孩子节点个数
                sum += dp[j] * dp[i - j - 1];
            }
            dp[i] = sum;
        }
        return dp[n];
    }
};
// @lc code=end
