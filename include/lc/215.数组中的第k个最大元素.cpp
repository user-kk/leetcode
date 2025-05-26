/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */
#include "common.h"

namespace {

// @lc code=start
class Solution {
   public:
    int findKthLargest(std::vector<int>& nums, int k) {
        return findKthLargest(nums, 0, nums.size() - 1, nums.size() - k);
    }
    // 快排写法的问题 ，标准答案中没有等号，导致一个极端例子很快nums[r] >= t
    int findKthLargest(std::vector<int>& nums, int first, int last, int k) {
        std::swap(nums[first], nums[first + (last - first) / 2]);
        int t = nums[first];
        int l = first;
        int r = last;
        while (l < r) {
            while (l < r && nums[r] >= t) {
                r--;
            }
            nums[l] = nums[r];

            while (l < r && nums[l] <= t) {
                l++;
            }
            nums[r] = nums[l];
        }
        nums[l] = t;

        if (l < k) {
            return findKthLargest(nums, l + 1, last, k);
        } else if (l > k) {
            return findKthLargest(nums, first, l - 1, k);
        } else {
            return t;
        }
    }
};
// @lc code=end
}  // namespace
