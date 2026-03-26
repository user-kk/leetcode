/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> ret;
    vector<int> path;
    // 只能选k之后的
    void dfs(vector<int>& nums, int k) {
        ret.push_back(path);
        for (int i = k; i < nums.size(); i++) {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(nums, 0);
        return ret;
    }
};
// @lc code=end
