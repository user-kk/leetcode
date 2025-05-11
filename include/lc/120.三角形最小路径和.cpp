/*
 * @lc app=leetcode.cn id=120 lang=cpp
 *
 * [120] 三角形最小路径和
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size();
        vector<vector<int>> dp(m, std::vector(m, 0));

        dp[0][0] = triangle[0][0];
        for (int i = 1; i < m; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0) {
                    dp[i][j] = triangle[i][j] + dp[i - 1][j];
                } else if (j == i) {
                    dp[i][j] = triangle[i][j] + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = triangle[i][j] +
                               std::min(dp[i - 1][j], dp[i - 1][j - 1]);
                }
            }
        }
        return *std::min_element(dp[m - 1].begin(), dp[m - 1].end());
    }
};
// @lc code=end
