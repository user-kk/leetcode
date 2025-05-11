/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */
#include <climits>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int right = 0;  // 左开右闭
        int cur = 0;
        int ret = INT_MAX;

        while (right < nums.size()) {
            while (cur < target && right < nums.size()) {
                cur += nums[right];
                right++;
            }
            while (cur >= target && left < right) {
                ret = std::min(ret, right - left);
                cur -= nums[left];
                left++;
            }
        }

        return ret == INT_MAX ? 0 : ret;
    }
};
// @lc code=end
