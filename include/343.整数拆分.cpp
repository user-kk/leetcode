/*
 * @lc app=leetcode.cn id=343 lang=cpp
 *
 * [343] 整数拆分
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 1);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i - 1; j++) {
                dp[i] = std::max({dp[i], j * dp[i - j], j * (i - j)});
            }
        }
        return dp[n];
    }
};
// @lc code=end
