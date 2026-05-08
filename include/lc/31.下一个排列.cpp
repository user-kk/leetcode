/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() == 1) {
            return;
        }
        int low = 0;
        //! 记住是从后往前
        // 从后向前遍历，找到第一个升序的（作为小值）
        // 再从后向前遍历，找到刚好比小值大一点的（作为大值）
        // 小值与大值互换，反转原本小值那个位置后面的序列
        for (int i = nums.size() - 1; i >= 1; i--) {
            if (nums[i - 1] < nums[i]) {
                int target = nums.size() - 1;
                for (int j = nums.size() - 1; j >= i; j--) {
                    if (nums[j] > nums[i - 1]) {
                        target = j;
                        break;
                    }
                }
                std::swap(nums[i - 1], nums[target]);
                low = i;
                break;
            }
        }
        std::reverse(nums.begin() + low, nums.end());
    }
};
// @lc code=end
