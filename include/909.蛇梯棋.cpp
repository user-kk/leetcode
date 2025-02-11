/*
 * @lc app=leetcode.cn id=909 lang=cpp
 *
 * [909] 蛇梯棋
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int snakesAndLadders(vector<vector<int>>& board) {
        vector<int> new_board;
        bool flag = true;  // 正序遍历
        int m = board.size();
        int n = board[0].size();
        new_board.reserve(m * n);
        for (int i = m - 1; i >= 0; i--) {
            if (flag) {
                for (int j = 0; j < n; j++) {
                    new_board.push_back(board[i][j]);
                }
            } else {
                for (int j = n - 1; j >= 0; j--) {
                    new_board.push_back(board[i][j]);
                }
            }
            flag = !flag;
        }
        struct T {
            int pos;
            int cost;
        };
        queue<T> q;
        q.push({0, 0});
        new_board[0] = -2;
        int min_cost = INT_MAX;
        while (!q.empty()) {
            auto [pos, cost] = q.front();
            q.pop();
            if (pos >= m * n - 1) {
                min_cost = std::min(min_cost, cost);
                continue;
            }
            bool flag = false;
            for (int i =
                     std::min(static_cast<int>(new_board.size()) - 1, pos + 6);
                 i >= pos + 1; i--) {
                if (new_board[i] != -1 && new_board[i] != -2 &&
                    new_board[new_board[i] - 1] != -2) {
                    new_board[new_board[i] - 1] = -2;
                    q.push({new_board[i] - 1, cost + 1});
                } else if (new_board[i] == -1 && !flag) {
                    q.push({i, cost + 1});
                    flag = true;
                }
                new_board[i] = -2;
            }
        }
        return min_cost == INT_MAX ? -1 : min_cost;
    }
};
// @lc code=end
