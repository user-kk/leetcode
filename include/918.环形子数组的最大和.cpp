/*
 * @lc app=leetcode.cn id=918 lang=cpp
 *
 * [918] 环形子数组的最大和
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxSubarraySumCircular(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        // 后缀和
        vector<int> sum(nums.size(), 0);

        // dp2[i]代表max(sum[i+1]..sum[n])
        vector<int> dp2(nums.size(), 0);

        dp[0] = nums[0];
        int ret = dp[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] + dp[i - 1] > nums[i]) {
                dp[i] = nums[i] + dp[i - 1];
            } else {
                dp[i] = nums[i];
            }
            if (dp[i] > ret) {
                ret = dp[i];
            }
        }

        sum.back() = nums.back();
        for (int i = nums.size() - 2; i >= 0; i--) {
            sum[i] = sum[i + 1] + nums[i];
        }

        int max_val = sum.back();
        for (int i = nums.size() - 1; i >= 0; i--) {
            dp2[i] = max_val;
            if (sum[i] > max_val) {
                max_val = sum[i];
            }
        }

        for (int i = 0; i < nums.size() - 1; i++) {
            if (dp2[i] > 0) {
                dp[i] = dp[i] + dp2[i];
            }
            if (dp[i] > ret) {
                ret = dp[i];
            }
        }
        return ret;
    }
};
// @lc code=end
