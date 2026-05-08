/*
 * @lc app=leetcode.cn id=80 lang=cpp
 *
 * [80] 删除有序数组中的重复项 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 1) {
            return 1;
        }

        int left = 1;
        int right = 1;

        int count = 0;
        for (; right < nums.size(); right++) {
            if (nums[right] == nums[right - 1]) {
                if (count == 0) {
                    count = 2;
                    nums[left++] = nums[right];
                }
            } else {
                count = 0;
                nums[left++] = nums[right];
            }
        }
        return left;
    }
};
// @lc code=end
