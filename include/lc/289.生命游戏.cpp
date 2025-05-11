/*
 * @lc app=leetcode.cn id=289 lang=cpp
 *
 * [289] 生命游戏
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int m = 0;
    int n = 0;
    bool checkIsLive(vector<vector<int>>& board, int i, int j) {
        return i >= 0 && i < m && j >= 0 && j < n &&
               ((board[i][j] & 0b01) == 1);
    }
    int live_num(vector<vector<int>>& board, int i, int j) {
        int ret = 0;
        if (checkIsLive(board, i - 1, j - 1)) {
            ret++;
        }
        if (checkIsLive(board, i - 1, j)) {
            ret++;
        }
        if (checkIsLive(board, i - 1, j + 1)) {
            ret++;
        }
        if (checkIsLive(board, i, j - 1)) {
            ret++;
        }
        if (checkIsLive(board, i, j + 1)) {
            ret++;
        }
        if (checkIsLive(board, i + 1, j + 1)) {
            ret++;
        }
        if (checkIsLive(board, i + 1, j)) {
            ret++;
        }
        if (checkIsLive(board, i + 1, j - 1)) {
            ret++;
        }
        return ret;
    }
    void gameOfLife(vector<vector<int>>& board) {
        m = board.size();
        n = board[0].size();
        // int的最低位的0 1代表上一轮的死 活
        // 最低位的高一位的0 1代表这一轮的死 活
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int num = live_num(board, i, j);
                if (board[i][j] == 0 && num == 3) {
                    board[i][j] = board[i][j] | 0b10;
                    continue;
                }

                if (board[i][j] == 1 && num >= 2 && num <= 3) {
                    board[i][j] = board[i][j] | 0b10;
                    continue;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = board[i][j] >> 1;
            }
        }
    }
};
// @lc code=end
