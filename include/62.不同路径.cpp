/*
 * @lc app=leetcode.cn id=62 lang=cpp
 *
 * [62] 不同路径
 */
#include <common.h>
#include <cmath>
#include <vector>
// @lc code=start
class Solution {
   public:
    // 函数用于计算组合数 C(m, n)
    long long combination(int m, int n) {
        long long a = 1;
        for (int i = 0; i < n; i++) {
            a = a * (m - i) / (i + 1);
        }

        return a;
    }
    int uniquePaths2(int m, int n) {
        return combination(m + n - 2, std::min(n - 1, m - 1));
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, std::vector(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};
// @lc code=end
