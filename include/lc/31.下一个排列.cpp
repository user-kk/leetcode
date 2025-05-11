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
