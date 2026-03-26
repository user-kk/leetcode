/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    struct T {
        int x;
        int y;
    };
    vector<vector<string>> ret;
    vector<T> path;

    void trans(int n) {
        vector<string> one_ret;
        for (auto [i, j] : path) {
            string s(n, '.');
            s[j] = 'Q';
            one_ret.push_back(std::move(s));
        }
        ret.push_back(std::move(one_ret));
    }
    bool check(int x, int y, int n) {
        for (auto [i, j] : path) {
            if (j == y) {
                return false;
            }
            //! 斜线：绝对值行减行等于列减列
            if (std::abs(x - i) == std::abs(y - j)) {
                return false;
            }
        }
        return true;
    }
    void dfs(int cur, int n) {
        if (cur == n) {
            trans(n);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (check(cur, i, n)) {
                path.push_back({cur, i});
                dfs(cur + 1, n);
                path.pop_back();
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        dfs(0, n);
        return ret;
    }
};
// @lc code=end
