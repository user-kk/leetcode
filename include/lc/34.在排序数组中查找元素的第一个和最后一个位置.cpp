/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ret(2, -1);
        if (nums.empty()) {
            return ret;
        }
        {
            int left = 0;
            int right = nums.size();
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (nums[mid] >= target) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            // 如果不是根本满足条件的或者满足条件的那个不是target，返回[-1,-1]
            if (left == nums.size() || nums[left] != target) {
                return ret;
            }
            ret[0] = left;
        }

        {
            int left = -1;
            int right = nums.size() - 1;
            while (left < right) {
                int mid = left + (right - left + 1) / 2;
                if (nums[mid] <= target) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            if (left == -1 || nums[left] != target) {
                return ret;
            }
            ret[1] = left;
        }

        return ret;
    }
};
// @lc code=end
