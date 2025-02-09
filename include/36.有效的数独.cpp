/*
 * @lc app=leetcode.cn id=36 lang=cpp
 *
 * [36] 有效的数独
 */
#include "common.h"
#include <bitset>
// @lc code=start
class Solution {
   public:
    bool isValidSudoku(vector<vector<char>>& board) {
        std::array<std::bitset<9>, 9> rows;
        std::array<std::bitset<9>, 9> cols;
        std::array<std::bitset<9>, 9> blocks;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int val = board[i][j] - '1';

                if (rows[i].test(val)) {
                    return false;
                } else {
                    rows[i].set(val, true);
                }

                if (cols[j].test(val)) {
                    return false;
                } else {
                    cols[j].set(val, true);
                }

                if (blocks[(i / 3) * 3 + (j / 3)].test(val)) {
                    return false;
                } else {
                    blocks[(i / 3) * 3 + (j / 3)].set(val, true);
                }
            }
        }
        return true;
    }
};
// @lc code=end
