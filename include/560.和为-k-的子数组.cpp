/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */
#include <common.h>

#include <vector>
// @lc code=start
class Solution {
   public:
    // 一段连续区间的值可直接使用前缀和相减得到
    int subarraySum(const vector<int>& nums, int k) {
        // 当遍历到i时，dp[j]代表从nums[j]->nums[i]的和

        if (nums.size() == 0) {
            return 0;
        }
        std::vector<int> prefixSum(nums.size());
        prefixSum[0] = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }
        int count = 0;

        std::unordered_map<int, int> m;

        //! 重要，排除两种特殊情况：前缀和本身为k,nums[0]为k
        m.insert({0, 1});

        for (int i = 0; i < nums.size(); i++) {
            if (auto it = m.find(prefixSum[i] - k); it != m.end()) {
                count += it->second;
            }
            if (auto it = m.find(prefixSum[i]); it != m.end()) {
                it->second++;
            } else {
                m.insert({prefixSum[i], 1});
            }
        }
        return count;
    }
};
// @lc code=end
