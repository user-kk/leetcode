/*
 * @lc app=leetcode.cn id=463 lang=cpp
 *
 * [463] 岛屿的周长
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int row = grid.size();
        int coloum = grid[0].size();
        int ret = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < coloum; j++) {
                if (grid[i][j] == 1) {
                    int count = 0;
                    if (i - 1 >= 0 && grid[i - 1][j] == 1) {
                        count++;
                    }
                    if (i + 1 < row && grid[i + 1][j] == 1) {
                        count++;
                    }
                    if (j - 1 >= 0 && grid[i][j - 1] == 1) {
                        count++;
                    }
                    if (j + 1 < coloum && grid[i][j + 1] == 1) {
                        count++;
                    }

                    ret += 4 - count;
                }
            }
        }
        return ret;
    }
};
// @lc code=end
