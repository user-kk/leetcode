/*
 * @lc app=leetcode.cn id=54 lang=cpp
 *
 * [54] 螺旋矩阵
 */
#include "common.h"

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

        struct Direction {
            int x;
            int y;
        };

        Direction directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        size_t di = 0;

        size_t step[2] = {col, row - 1};

        //! 注意不能先走（0,0），先走了step[0]就不是col了，而是col-1了，导致后续的step[0]和step[1]都不对了
        int pos[2] = {0, -1};

        while (ret.size() < row * col) {
            for (int i = 0; i < step[di % 2]; i++) {
                //! 别加反了，因为directions里是先x后y的，所以pos[0]要加y，pos[1]要加x
                pos[0] += directions[di].y;
                pos[1] += directions[di].x;
                ret.push_back(m[pos[0]][pos[1]]);
            }

            step[di % 2]--;  //! 每走完一个方向就要减少对应维度的步数
                             //! 0,2行减一 1,3列减一

            di = (di + 1) % 4;
        }
        return ret;
    }
};
// @lc code=end
