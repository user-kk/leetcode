/*
 * @lc app=leetcode.cn id=90 lang=cpp
 *
 * [90] 子集 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> ret;
    vector<int> path;

    void dfs(const vector<int>& nums, int start) {
        ret.push_back(path);

        std::optional<int> last_val;

        for (int i = start; i < nums.size(); i++) {
            if (last_val.has_value() && nums[i] == last_val) {
                continue;
            }

            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
            last_val = nums[i];
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        std::ranges::sort(nums);
        dfs(nums, 0);
        return ret;
    }
};
// @lc code=end
