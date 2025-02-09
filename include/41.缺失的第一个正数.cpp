/*
 * @lc app=leetcode.cn id=41 lang=cpp
 *
 * [41] 缺失的第一个正数
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == i + 1) {
                continue;
            }
            if (1 <= nums[i] && nums[i] <= n) {
                //! 被交换的位置原来不能有等于自己的值
                if (nums[nums[i] - 1] != nums[i]) {
                    std::swap(nums[i], nums[nums[i] - 1]);
                    i--;
                }
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};
// @lc code=end
