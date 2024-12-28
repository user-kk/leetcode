/*
 * @lc app=leetcode.cn id=153 lang=cpp
 *
 * [153] 寻找旋转排序数组中的最小值
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    int findMin(vector<int>& nums) {
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
};
// @lc code=end
