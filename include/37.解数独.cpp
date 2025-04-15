/*
 * @lc app=leetcode.cn id=37 lang=cpp
 *
 * [37] 解数独
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    std::vector<std::bitset<9>> rows;
    std::vector<std::bitset<9>> cols;
    std::vector<std::bitset<9>> blocks;

    bool set(vector<vector<char>>& board, int i, int j, int v) {
        if (rows[i].test(v - 1)) {
            return false;
        }
        if (cols[j].test(v - 1)) {
            return false;
        }
        if (blocks[get_block_id(i, j)].test(v - 1)) {
            return false;
        }

        rows[i].set(v - 1);
        cols[j].set(v - 1);
        blocks[get_block_id(i, j)].set(v - 1);
        board[i][j] = '0' + v;
        return true;
    }
    void unset(vector<vector<char>>& board, int i, int j, int v) {
        rows[i].set(v - 1, false);
        cols[j].set(v - 1, false);
        blocks[get_block_id(i, j)].set(v - 1, false);
        board[i][j] = '.';
    }
    bool dfs(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == '.') {
                    for (int v = 1; v <= 9; v++) {
                        if (set(board, i, j, v)) {
                            if (dfs(board)) {
                                return true;
                            }
                            unset(board, i, j, v);
                        }
                    }
                    // 9个都穷举过了，还没成功
                    return false;
                }
            }
        }
        return true;
    }
    static int get_block_id(int i, int j) { return (i / 3) * 3 + (j / 3); }
    void init(vector<vector<char>>& board) {
        rows.assign(9, {});
        cols.assign(9, {});
        blocks.assign(9, {});
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] != '.') {
                    rows[i].set(board[i][j] - '1');
                    cols[j].set(board[i][j] - '1');
                    blocks[get_block_id(i, j)].set(board[i][j] - '1');
                }
            }
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        init(board);
        dfs(board);
    }
};
// @lc code=end
