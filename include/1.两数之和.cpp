/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            auto it = map.find(target - nums[i]);
            if (it == map.end()) {
                map.insert({nums[i], i});
                continue;
            }
            return {
                it->second,
                i,
            };
        }
        return {};
    }
};
// @lc code=end
