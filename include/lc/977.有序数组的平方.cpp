/*
 * @lc app=leetcode.cn id=977 lang=cpp
 *
 * [977] 有序数组的平方
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ret;
        ret.reserve(nums.size());
        auto it = std::ranges::min_element(
            nums, [](int a, int b) { return std::abs(a) < std::abs(b); });
        int pos = it - nums.begin();
        ret.push_back(nums[pos] * nums[pos]);

        int left = pos - 1;
        int right = pos + 1;
        while (left >= 0 || right <= nums.size() - 1) {
            int left_val = left >= 0 ? nums[left] : INT_MAX;
            int right_val = right <= nums.size() - 1 ? nums[right] : INT_MAX;
            if (std::abs(left_val) < std::abs(right_val)) {
                ret.push_back(left_val * left_val);
                left--;
            } else {
                ret.push_back(right_val * right_val);
                right++;
            }
        }
        return ret;
    }
};
// @lc code=end
