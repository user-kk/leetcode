/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 1 || n == 2) {
            return 0;
        }
        int left = 0;
        int right = n - 1;
        int left_max = height[left];    // left及left左侧的最大值
        int right_max = height[right];  // right及right右侧的最大值
        int ret = 0;

        // 每一个点的值为min(点左侧的max,点右侧的max)-该点的值

        // left和right指向的是要进行计算的那一列
        while (left <= right) {
            if (height[left] > left_max) {
                left_max = height[left];
            }
            if (height[right] > right_max) {
                right_max = height[right];
            }

            if (left_max < right_max) {
                // 这种情况下，能够确定在left这一点上min(left左侧的max,left右侧的max)==left左侧的max
                ret += left_max - height[left];
                left++;
            } else {
                // 这种情况下，能够确定在right这一点上min(right左侧的max,right右侧的max)==right右侧的max
                ret += right_max - height[right];
                right--;
            }
        }
        return ret;
    }
};
// @lc code=end
