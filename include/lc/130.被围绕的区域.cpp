/*
 * @lc app=leetcode.cn id=130 lang=cpp
 *
 * [130] 被围绕的区域
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    struct T {
        int x;
        int y;
    };
    static bool isVaild(T pos, int m, int n) {
        return pos.x >= 0 && pos.x < m && pos.y >= 0 && pos.y < n;
    }
    void bfs(vector<vector<char>>& board, T start, int m, int n) {
        std::queue<T> q;
        board[start.x][start.y] = 'k';
        q.push(start);
        while (!q.empty()) {
            T pos = q.front();
            q.pop();
            if (T new_pos = {pos.x - 1, pos.y};
                isVaild(new_pos, m, n) && board[new_pos.x][new_pos.y] == 'O') {
                board[new_pos.x][new_pos.y] = 'k';
                q.push(new_pos);
            }
            if (T new_pos = {pos.x + 1, pos.y};
                isVaild(new_pos, m, n) && board[new_pos.x][new_pos.y] == 'O') {
                board[new_pos.x][new_pos.y] = 'k';
                q.push(new_pos);
            }
            if (T new_pos = {pos.x, pos.y - 1};
                isVaild(new_pos, m, n) && board[new_pos.x][new_pos.y] == 'O') {
                board[new_pos.x][new_pos.y] = 'k';
                q.push(new_pos);
            }
            if (T new_pos = {pos.x, pos.y + 1};
                isVaild(new_pos, m, n) && board[new_pos.x][new_pos.y] == 'O') {
                board[new_pos.x][new_pos.y] = 'k';
                q.push(new_pos);
            }
        }
    }
    //! 从边界出发
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < n; i++) {
            if (board[0][i] == 'O') {
                bfs(board, {0, i}, m, n);
            }
        }
        for (int i = 1; i < m - 1; i++) {
            if (board[i][0] == 'O') {
                bfs(board, {i, 0}, m, n);
            }
            if (n - 1 > 0 && board[i][n - 1] == 'O') {
                bfs(board, {i, n - 1}, m, n);
            }
        }
        if (m - 1 > 0) {
            for (int i = 0; i < n; i++) {
                if (board[m - 1][i] == 'O') {
                    bfs(board, {m - 1, i}, m, n);
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'k') {
                    board[i][j] = 'O';
                } else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};
// @lc code=end
