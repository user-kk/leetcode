/*
 * @lc app=leetcode.cn id=33 lang=cpp
 *
 * [33] 搜索旋转排序数组
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int findMax(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            if (left == right) {
                return left;
            }
            if (left + 1 == right) {
                return nums[left] < nums[right] ? right : left;
            }
            int mid = (left + right) / 2;

            if (nums[mid] > nums[left] && nums[mid] > nums[right]) {
                left = mid;
            } else if (nums[mid] < nums[left] && nums[mid] < nums[right]) {
                right = mid - 1;
            } else if (nums[left] < nums[mid] && nums[mid] < nums[right]) {
                left = mid + 1;
            }
        }
        return -1;
    }
    int binarySearch(vector<int>& nums, int left, int right, int target) {
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                return mid;
            }
        }
        return -1;
    }
    int search2(vector<int>& nums, int target) {
        if (nums.size() == 1) {
            return nums[0] == target ? 0 : -1;
        }
        int max_index = findMax(nums);
        if (target > nums[0]) {
            return binarySearch(nums, 0, max_index, target);
        } else if (target < nums[0]) {
            return binarySearch(nums, max_index + 1, nums.size() - 1, target);
        } else {
            return 0;
        }
    }

    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r) {
            int mid = l + ((r - l) / 2);
            if (nums[mid] == target) {
                return mid;
            }
            //! 必须要大于等于而非大于，例如[2,1] 1
            if (nums[mid] >= nums[0]) {  // l 到 mid 有序
                if (nums[l] <= target && target <= nums[mid]) {  // 在有序区间内
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {  //  mid 到 r 有序
                if (nums[mid] <= target && target <= nums[r]) {  // 在有序区间内
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};
// @lc code=end
