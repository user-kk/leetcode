/*
 * @lc app=leetcode.cn id=491 lang=cpp
 *
 * [491] 非递减子序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> ret;
    vector<int> path;

    void dfs(const vector<int>& nums, int start) {
        if (path.size() >= 2) {
            ret.push_back(path);
        }

        std::unordered_set<int> visited;

        for (int i = start; i < nums.size(); i++) {
            if (visited.contains(nums[i])) {
                continue;
            }
            if (path.empty() || nums[i] >= path.back()) {
                path.push_back(nums[i]);
                dfs(nums, i + 1);
                path.pop_back();
                visited.insert(nums[i]);
            }
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        dfs(nums, 0);
        return ret;
    }
};
// @lc code=end
