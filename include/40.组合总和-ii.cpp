/*
 * @lc app=leetcode.cn id=40 lang=cpp
 *
 * [40] 组合总和 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> ret;
    vector<int> path;
    int _target;
    void dfs(const vector<int>& candidates, int start, int cur) {
        if (cur > _target) {
            return;
        }
        if (cur == _target) {
            ret.push_back(path);
            return;
        }

        int last_val = -1;

        for (int i = start; i < candidates.size(); i++) {
            if (candidates[i] == last_val) {
                continue;
            }

            path.push_back(candidates[i]);
            dfs(candidates, i + 1, cur + candidates[i]);
            path.pop_back();
            last_val = candidates[i];
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        std::ranges::sort(candidates);
        _target = target;
        dfs(candidates, 0, 0);
        return ret;
    }
};
// @lc code=end
