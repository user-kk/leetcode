/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    vector<int> t;
    void dfs(vector<int>& candidate, vector<vector<int>>& ret, int val,
             int target, int current_i) {
        if (val == target) {
            ret.push_back(t);
            return;
        }
        if (val > target) {
            return;
        }

        for (int i = current_i; i < candidate.size(); i++) {
            t.push_back(candidate[i]);
            dfs(candidate, ret, val + candidate[i], target, i);
            t.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidate, int target) {
        vector<vector<int>> ret;
        dfs(candidate, ret, 0, target, 0);
        return ret;
    }
};
// @lc code=end
