/*
 * @lc app=leetcode.cn id=189 lang=cpp
 *
 * [189] 轮转数组
 */
#include "common.h"

#include <algorithm>
// @lc code=start
class Solution {
   public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        if (k == 0) {
            return;
        }

        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
    }
};
// @lc code=end
