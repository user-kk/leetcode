/*
 * @lc app=leetcode.cn id=221 lang=cpp
 *
 * [221] 最大正方形
 */
#include <common.h>
namespace {

// @lc code=start
class Solution {
   public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int row = matrix.size();
        int coloum = matrix[0].size();
        vector<vector<int>> dp(row, vector<int>(coloum, 0));

        for (int i = 0; i < coloum; i++) {
            if (matrix[0][i] == '1') {
                dp[0][i] = 1;
            }
        }

        for (int i = 0; i < row; i++) {
            if (matrix[i][0] == '1') {
                dp[i][0] = 1;
            }
        }

        for (int i = 1; i < row; i++) {
            for (int j = 1; j < coloum; j++) {
                if (matrix[i][j] == '0') {
                    continue;
                }

                int a = dp[i - 1][j - 1];
                int b = dp[i - 1][j];
                int c = dp[i][j - 1];
                dp[i][j] = std::min({a, b, c}) + 1;
            }
        }

        int _max = -1;
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < coloum; j++) {
                if (matrix[i][j] == '0') {
                    continue;
                }

                int a = dp[i - 1][j - 1];
                int b = dp[i - 1][j];
                int c = dp[i][j - 1];
                dp[i][j] = std::min({a, b, c}) + 1;
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < coloum; j++) {
                if (dp[i][j] > _max) {
                    _max = dp[i][j];
                }
            }
        }
        return _max * _max;
    }
};
// @lc code=end
}  // namespace
