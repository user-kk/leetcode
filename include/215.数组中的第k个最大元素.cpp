/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */
#include <common.h>

namespace {
// 快排写法的问题 ，标准答案中没有等号，导致一个极端例子很快nums[r] >= t
int findKthLargest(std::vector<int>& nums, int first, int last, int k) {
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

    if (r < nums.size() - k) {
        return findKthLargest(nums, r + 1, last, k);
    } else if (r > nums.size() - k) {
        return findKthLargest(nums, first, r - 1, k);
    } else {
        return t;
    }
}

// @lc code=start
class Solution {
   public:
    // int findKthLargest(std::vector<int>& nums, int l, int r, int k) {
    //     if (l == r) return nums[k];
    //     int partition = nums[l], i = l - 1, j = r + 1;
    //     while (i < j) {
    //         do i++;
    //         while (nums[i] < partition);
    //         do j--;
    //         while (nums[j] > partition);
    //         if (i < j) {
    //             swap(nums[i], nums[j]);
    //         }
    //     }
    //     if (k <= j) {
    //         return findKthLargest(nums, l, j, k);
    //     } else {
    //         return findKthLargest(nums, j + 1, r, k);
    //     }
    // }

    int findKthLargest(std::vector<int>& nums, int k) {
        return findKthLargest(nums, 0, nums.size() - 1, nums.size() - k);
    }
    int findKthLargest(std::vector<int>& nums, int first, int last, int k) {
        int t = nums[first];
        int l = first;
        int r = last;
        while (l < r) {
            while (l < r && nums[r] >= t) {
                r--;
            }
            nums[l] = nums[r];

            while (l < r && nums[l] < t) {
                l++;
            }
            nums[r] = nums[l];
        }
        nums[l] = t;

        if (r < k) {
            return findKthLargest(nums, r + 1, last, k);
        } else if (r > k) {
            return findKthLargest(nums, first, r - 1, k);
        } else {
            return t;
        }
    }
};
// @lc code=end
}  // namespace
