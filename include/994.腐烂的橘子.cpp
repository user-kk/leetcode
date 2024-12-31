/*
 * @lc app=leetcode.cn id=994 lang=cpp
 *
 * [994] 腐烂的橘子
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    struct Pos {
        int row;
        int col;
    };
    void init(const vector<vector<int>>& grid, std::queue<Pos>& bad,
              int& bad_num, int& good_num) {
        bad_num = 0;
        good_num = 0;
        size_t row_num = grid.size();
        size_t col_num = grid[0].size();
        for (size_t i = 0; i < row_num; i++) {
            for (size_t j = 0; j < col_num; j++) {
                if (grid[i][j] == 2) {
                    bad_num++;
                    bad.push(Pos{static_cast<int>(i), static_cast<int>(j)});
                } else if (grid[i][j] == 1) {
                    good_num++;
                }
            }
        }
    }
    void rot(vector<vector<int>>& grid, Pos pos, std::queue<Pos>& bad,
             int& good_num) {
        size_t row_num = grid.size();
        size_t col_num = grid[0].size();
        if (pos.row - 1 >= 0 && grid[pos.row - 1][pos.col] == 1) {
            grid[pos.row - 1][pos.col] = 2;
            good_num--;
            bad.push({pos.row - 1, pos.col});
        }
        if (pos.col + 1 < col_num && grid[pos.row][pos.col + 1] == 1) {
            grid[pos.row][pos.col + 1] = 2;
            good_num--;
            bad.push({pos.row, pos.col + 1});
        }
        if (pos.row + 1 < row_num && grid[pos.row + 1][pos.col] == 1) {
            grid[pos.row + 1][pos.col] = 2;
            good_num--;
            bad.push({pos.row + 1, pos.col});
        }
        if (pos.col - 1 >= 0 && grid[pos.row][pos.col - 1] == 1) {
            grid[pos.row][pos.col - 1] = 2;
            good_num--;
            bad.push({pos.row, pos.col - 1});
        }
    }
    int orangesRotting(vector<vector<int>>& grid) {
        std::queue<Pos> bad;
        std::queue<Pos> bad2;
        int bad_num = 0;
        int good_num = 0;
        int time = 0;
        init(grid, bad, bad_num, good_num);
        if (good_num == 0) {
            return time;
        }
        while (!bad.empty() || !bad2.empty()) {
            while (!bad.empty()) {
                rot(grid, bad.front(), bad2, good_num);
                bad.pop();
            }
            time++;
            if (good_num == 0) {
                break;
            }

            while (!bad2.empty()) {
                rot(grid, bad2.front(), bad, good_num);
                bad2.pop();
            }
            time++;
            if (good_num == 0) {
                break;
            }
        }
        return good_num != 0 ? -1 : time;
    }
};
// @lc code=end
