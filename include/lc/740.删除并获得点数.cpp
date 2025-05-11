/*
 * @lc app=leetcode.cn id=740 lang=cpp
 *
 * [740] 删除并获得点数
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int deleteAndEarn(vector<int>& nums) {
        std::ranges::sort(nums);
        struct T {
            int val;
            int count;
        };
        vector<T> k;

        for (int i = 0; i < nums.size(); i++) {
            if (k.empty()) {
                k.push_back(T{nums[i], 1});
                continue;
            }

            if (nums[i] == k.back().val) {
                k.back().count++;
            } else {
                k.push_back(T{nums[i], 1});
            }
        }

        vector<int> dp(k.size(), 0);
        dp[0] = k[0].count * k[0].val;
        if (k.size() >= 2) {
            if (k[1].val == k[0].val + 1) {
                dp[1] = std::max(dp[0], k[1].count * k[1].val);
            } else {
                dp[1] = dp[0] + k[1].count * k[1].val;
            }
        }

        for (int i = 2; i < k.size(); i++) {
            if (k[i].val == k[i - 1].val + 1) {
                dp[i] = std::max(dp[i - 1], dp[i - 2] + k[i].count * k[i].val);
            } else {
                dp[i] = dp[i - 1] + k[i].count * k[i].val;
            }
        }

        return dp.back();
    }
};
// @lc code=end
