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
        // dp2[i]代表max(sum[i+1]..sum[n]),sum为后缀和
        vector<int> dp2(nums.size(), 0);

        int post_sum = 0;  // 后缀和
        int max_sum = INT_MIN;
        for (int i = nums.size() - 1; i >= 0; i--) {
            dp2[i] = max_sum;
            post_sum += nums[i];
            if (post_sum > max_sum) {
                max_sum = post_sum;
            }
        }
        dp2.back() = 0;

        dp[0] = nums[0];
        int pre_sum = dp[0];  // 前缀和

        int ret = std::max(dp[0], pre_sum + dp2[0]);
        for (int i = 1; i < nums.size(); i++) {
            pre_sum += nums[i];
            if (nums[i] + dp[i - 1] > nums[i]) {
                dp[i] = nums[i] + dp[i - 1];
            } else {
                dp[i] = nums[i];
            }
            int val = std::max(dp[i], pre_sum + dp2[i]);
            if (val > ret) {
                ret = val;
            }
        }

        return ret;
    }
};
// @lc code=end
