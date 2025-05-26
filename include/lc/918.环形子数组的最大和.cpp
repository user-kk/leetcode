/*
 * @lc app=leetcode.cn id=918 lang=cpp
 *
 * [918] 环形子数组的最大和
 */
#include <numeric>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int maxSubarraySumCircular2(vector<int>& nums) {
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

    int maxSubarraySumCircular(vector<int>& nums) {
        vector<int> max_dp(nums.size());
        vector<int> min_dp(nums.size());

        max_dp[0] = nums[0];
        min_dp[0] = nums[0];

        int max_v = nums[0];
        int min_v = nums[0];

        int sum = std::accumulate(nums.begin(), nums.end(), 0);

        for (int i = 1; i < nums.size(); i++) {
            max_dp[i] = std::max(nums[i], max_dp[i - 1] + nums[i]);
            max_v = std::max(max_v, max_dp[i]);
            min_dp[i] = std::min(nums[i], min_dp[i - 1] + nums[i]);
            min_v = std::min(min_v, min_dp[i]);
        }

        // 防止全为负数时返回零
        if (min_v == sum) {
            return max_v;
        }

        // 或是不发生回环时最大值，或是sum - 不发生回环的最小值
        return std::max(max_v, sum - min_v);
    }
};
// @lc code=end
