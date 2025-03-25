/*
 * @lc app=leetcode.cn id=162 lang=cpp
 *
 * [162] 寻找峰值
 */
#include <climits>
#include <cstdint>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int64_t mid_l_v = mid - 1 >= 0 ? nums[mid - 1] : INT64_MIN;
            int64_t mid_r_v = mid + 1 < nums.size() ? nums[mid + 1] : INT64_MIN;
            if (nums[mid] > mid_l_v && nums[mid] > mid_r_v) {
                return mid;
            }
            if (nums[mid] < mid_l_v && nums[mid] < mid_r_v) {
                right = mid - 1;
                continue;
            }

            if (mid_l_v < nums[mid] && nums[mid] < mid_r_v) {
                left = mid + 1;
                continue;
            }

            if (mid_l_v > nums[mid] && nums[mid] > mid_r_v) {
                right = mid - 1;
                continue;
            }
        }
        return -1;
    }
};
// @lc code=end
