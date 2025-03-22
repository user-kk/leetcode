/*
 * @lc app=leetcode.cn id=77 lang=cpp
 *
 * [77] 组合
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> ret;
    int _n;
    int _k;
    void dfs(vector<int>& result, int pos) {
        if (result.size() == _k) {
            ret.push_back(result);
            return;
        }
        for (int i = pos; i <= _n; i++) {
            result.push_back(i);
            dfs(result, i + 1);
            result.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        _n = n;
        _k = k;
        vector<int> result;
        result.reserve(k);
        dfs(result, 1);
        return ret;
    }
};
// @lc code=end
