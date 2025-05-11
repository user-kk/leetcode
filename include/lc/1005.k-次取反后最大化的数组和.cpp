/*
 * @lc app=leetcode.cn id=1005 lang=cpp
 *
 * [1005] K 次取反后最大化的数组和
 */
#include <algorithm>
#include <functional>
#include <numeric>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end(),
                  [](int a, int b) { return std::abs(a) < std::abs(b); });

        for (int i = nums.size() - 1; i >= 0; i--) {
            if (k > 0) {
                if (nums[i] < 0) {
                    nums[i] = -nums[i];
                    k--;
                }
            } else {
                return std::accumulate(nums.begin(), nums.end(), 0);
            }
        }

        if (k % 2 == 1) {
            nums[0] = -nums[0];
        }

        return std::accumulate(nums.begin(), nums.end(), 0);
    }
};
// @lc code=end
