/*
 * @lc app=leetcode.cn id=674 lang=cpp
 *
 * [674] 最长连续递增序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int findLengthOfLCIS(vector<int>& nums) {
        int dp = 1;
        int ret = 1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                dp = dp + 1;
                ret = std::max(ret, dp);
            } else {
                dp = 1;
            }
        }
        return ret;
    }
};
// @lc code=end
