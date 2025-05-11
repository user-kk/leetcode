/*
 * @lc app=leetcode.cn id=59 lang=cpp
 *
 * [59] 螺旋矩阵 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ret(n, vector<int>(n, 0));
        int v = 1;
        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;
        int i = 0, j = 0;

        while (v <= n * n) {
            for (j = left; j <= right; j++) {
                ret[i][j] = v++;
            }
            top++;
            j--;
            for (i = top; i <= bottom; i++) {
                ret[i][j] = v++;
            }
            right--;
            i--;
            for (j = right; j >= left; j--) {
                ret[i][j] = v++;
            }
            bottom--;
            j++;
            for (i = bottom; i >= top; i--) {
                ret[i][j] = v++;
            }
            left++;
            i++;
        }

        return ret;
    }
};
// @lc code=end
