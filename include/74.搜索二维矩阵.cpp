/*
 * @lc app=leetcode.cn id=74 lang=cpp
 *
 * [74] 搜索二维矩阵
 */
#include <common.h>

#include <utility>
// @lc code=start
class Solution {
   public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        auto& m = matrix;
        int row = matrix.size();
        int col = matrix[0].size();

        int low = 0;
        int high = row * col - 1;
        auto getPos = [row, col](int n) {
            return std::make_pair(n / col, n % col);
        };

        while (low <= high) {
            int mid = (low + high) / 2;
            auto [i, j] = getPos(mid);
            if (m[i][j] == target) {
                return true;
            }
            if (m[i][j] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }
};
// @lc code=end
