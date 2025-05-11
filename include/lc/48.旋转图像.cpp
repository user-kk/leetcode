/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 竖向翻转
    void flip1(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                std::swap(matrix[i][j], matrix[i][n - j - 1]);
            }
        }
    }

    // 副对角线翻转
    void flip2(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                std::swap(matrix[i][j], matrix[n - j - 1][n - i - 1]);
            }
        }
    }
    void rotate(vector<vector<int>>& matrix) {
        flip1(matrix);
        flip2(matrix);
    }
};
// @lc code=end
