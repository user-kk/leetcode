/*
 * @lc app=leetcode.cn id=216 lang=cpp
 *
 * [216] 组合总和 III
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> ret;
    int _k;
    int _n;
    vector<int> one_ret;

    void dfs(int depth, int start, int cur) {
        if (cur > _n) {
            return;
        }
        if (depth == _k + 1) {
            if (cur == _n) {
                ret.push_back(one_ret);
            }
            return;
        }
        for (int i = start; i <= 9; i++) {
            one_ret.push_back(i);
            dfs(depth + 1, i + 1, cur + i);
            one_ret.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        _k = k;
        _n = n;
        one_ret.reserve(k);
        dfs(1, 1, 0);
        return ret;
    }
};
// @lc code=end
