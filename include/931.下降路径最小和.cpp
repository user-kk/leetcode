/*
 * @lc app=leetcode.cn id=931 lang=cpp
 *
 * [931] 下降路径最小和
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        vector<vector<int>> dp(matrix);

        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (j == 0) {
                    dp[i][j] =
                        matrix[i][j] + std::min(dp[i - 1][j], dp[i - 1][j + 1]);
                } else if (j == matrix[0].size() - 1) {
                    dp[i][j] =
                        matrix[i][j] + std::min(dp[i - 1][j], dp[i - 1][j - 1]);
                } else {
                    dp[i][j] =
                        matrix[i][j] + std::min({dp[i - 1][j], dp[i - 1][j + 1],
                                                 dp[i - 1][j - 1]});
                }
            }
        }

        return *std::min_element(dp[dp.size() - 1].begin(),
                                 dp[dp.size() - 1].end());
    }
};
// @lc code=end
