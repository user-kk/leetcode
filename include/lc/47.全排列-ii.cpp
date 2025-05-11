/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> ret;
    vector<int> path;
    vector<bool> visited;

    void dfs(vector<int>& nums) {
        if (std::all_of(visited.begin(), visited.end(),
                        [](bool v) { return v; })) {
            ret.push_back(path);
            return;
        }
        int last_visited_i = -1;  // 上一次被访问过的i

        for (int i = 0; i < visited.size(); i++) {
            if (visited[i]) {
                continue;
            }
            if (last_visited_i != -1 && nums[i] == nums[last_visited_i]) {
                continue;
            }
            path.push_back(nums[i]);
            visited[i] = true;
            last_visited_i = i;
            dfs(nums);
            visited[i] = false;
            path.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        //! 遇到结果要去重的，想排序，先把输入排序一遍，然后在遍历的时候跳过重复的
        std::ranges::sort(nums);
        path.reserve(nums.size());
        visited.assign(nums.size(), false);
        dfs(nums);
        return ret;
    }
};
// @lc code=end
