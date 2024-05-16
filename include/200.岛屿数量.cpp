/*
 * @lc app=leetcode.cn id=200 lang=cpp
 *
 * [200] 岛屿数量
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    // DFS与树遍历的区别：树遍历不会记录哪个点已经被遍历过了
    // 而DFS会记录点已经被遍历过了，所以不递归的树的后序遍历必须记录栈顶是否为遍历过了
    // DFS遍历树时，从栈顶弹出的可以向左右走（因为会记录左边已经遍历过了）
    // 而后序遍历树时，弹栈后只能向右走，不能向左走，否则会陷入左走->弹栈->左走->弹栈->...
    int numIslands(vector<vector<char>>& grid) {
        int ret = 0;
        struct E {
            int x;
            int y;
        };
        std::stack<E> s;
        int row = grid.size();
        int coloum = grid[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < coloum; j++) {
                if (grid[i][j] == '1') {
                    grid[i][j] = '0';
                    ret++;
                    s.push({i, j});
                    while (!s.empty()) {
                        E v = s.top();
                        if (v.x - 1 >= 0 && grid[v.x - 1][v.y] == '1') {
                            grid[v.x - 1][v.y] = '0';
                            s.push({v.x - 1, v.y});
                            continue;
                        }
                        if (v.y + 1 < coloum && grid[v.x][v.y + 1] == '1') {
                            grid[v.x][v.y + 1] = '0';
                            s.push({v.x, v.y + 1});
                            continue;
                        }
                        if (v.x + 1 < row && grid[v.x + 1][v.y] == '1') {
                            grid[v.x + 1][v.y] = '0';
                            s.push({v.x + 1, v.y});
                            continue;
                        }
                        s.pop();
                        if (v.y - 1 >= 0 && grid[v.x][v.y - 1] == '1') {
                            grid[v.x][v.y - 1] = '0';
                            s.push({v.x, v.y - 1});
                        }
                    }
                }
            }
        }
        return ret;
    }
};
// @lc code=end
