/*
 * @lc app=leetcode.cn id=152 lang=cpp
 *
 * [152] 乘积最大子数组
 */
#include <climits>

#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxProduct(vector<int>& nums) {
        vector<int> max(nums.size());
        vector<int> min(nums.size());
        max[0] = nums[0];
        min[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            max[i] =
                std::max({max[i - 1] * nums[i], min[i - 1] * nums[i], nums[i]});
            min[i] =
                std::min({max[i - 1] * nums[i], min[i - 1] * nums[i], nums[i]});
        }
        return *std::ranges::max_element(max);
    }
};
// @lc code=end
