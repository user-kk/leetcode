/*
 * @lc app=leetcode.cn id=54 lang=cpp
 *
 * [54] 螺旋矩阵
 */
#include <common.h>

#include <cstddef>
// @lc code=start
class Solution {
   public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        auto& m = matrix;
        size_t row = m.size();
        size_t col = m[0].size();
        vector<int> ret;
        ret.reserve(row * col);

        int i = 0;
        int j = 0;
        int right = col;
        int down = row;
        int left = -1;
        int up = 0;

        while (true) {
            if (j == right) {
                break;
            }
            for (; j < right; j++) {
                ret.push_back(m[i][j]);
            }
            j--;
            i++;
            right--;

            if (i == down) {
                break;
            }
            for (; i < down; i++) {
                ret.push_back(m[i][j]);
            }
            i--;
            j--;
            down--;

            if (j == left) {
                break;
            }
            for (; j > left; j--) {
                ret.push_back(m[i][j]);
            }
            j++;
            i--;
            left++;

            if (i == up) {
                break;
            }
            for (; i > up; i--) {
                ret.push_back(m[i][j]);
            }
            i++;
            j++;
            up++;
        }
        return ret;
    }
};
// @lc code=end
