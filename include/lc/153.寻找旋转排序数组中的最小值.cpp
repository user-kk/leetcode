/*
 * @lc app=leetcode.cn id=153 lang=cpp
 *
 * [153] 寻找旋转排序数组中的最小值
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int findMin2(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            if (left == right) {
                return nums[left];
            }

            if (left + 1 == right) {
                return std::min(nums[left], nums[right]);
            }

            // 这个地方 num[left]!=num[mid]!=num[right]一定成立
            int mid = (left + right) / 2;
            if (nums[mid] > nums[left] && nums[mid] > nums[right]) {
                left = mid + 1;
            } else if (nums[mid] < nums[left] && nums[mid] < nums[right]) {
                right = mid;
            } else if (nums[left] < nums[mid] && nums[mid] < nums[right]) {
                right = mid - 1;
            }
        }
        return -1;
    }
    int findMin(vector<int>& nums) {
        int ret = INT_MAX;
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            //! 先更新有序阶段的最小值，然后去无序阶段重新找
            if (nums[0] <= nums[mid]) {  // l 到 mid 有序
                ret = std::min(ret, nums[l]);
                l = mid + 1;
            } else {
                ret = std::min(ret, nums[mid]);
                r = mid - 1;
            }
        }
        return ret;
    }
};
// @lc code=end
