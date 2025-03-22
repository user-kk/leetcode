/*
 * @lc app=leetcode.cn id=909 lang=cpp
 *
 * [909] 蛇梯棋
 */
#include <fmt/base.h>
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
        vector<bool> visited(m * n, false);
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
        queue<int> q1;
        queue<int> q2;
        q1.push(0);

        int cost = 0;
        while (!q1.empty() || !q2.empty()) {
            while (!q1.empty()) {
                int pos = q1.front();
                q1.pop();
                visited[pos] = true;
                // 如果到了
                if (pos >= m * n - 1) {
                    return cost;
                }

                bool flag = false;
                for (int i = std::min(static_cast<int>(new_board.size()) - 1,
                                      pos + 6);
                     i >= pos + 1; i--) {
                    if (new_board[i] == -1) {
                        if (!flag) {
                            q2.push(i);
                            flag = true;
                        } else {
                            visited[i] = true;
                        }
                        continue;
                    }

                    if (!visited[new_board[i] - 1]) {
                        q2.push(new_board[i] - 1);
                        visited[i] = true;
                    }
                }
            }
            cost++;
            while (!q2.empty()) {
                int pos = q2.front();
                q2.pop();
                visited[pos] = true;
                // 如果到了
                if (pos >= m * n - 1) {
                    return cost;
                }

                bool flag = false;
                for (int i = std::min(static_cast<int>(new_board.size()) - 1,
                                      pos + 6);
                     i >= pos + 1; i--) {
                    if (new_board[i] == -1) {
                        if (!flag) {
                            q1.push(i);
                            flag = true;
                        } else {
                            visited[i] = true;
                        }
                        continue;
                    }

                    if (!visited[new_board[i] - 1]) {
                        q1.push(new_board[i] - 1);
                        visited[i] = true;
                    }
                }
            }
            cost++;
        }
        return -1;
    }
};
// @lc code=end
