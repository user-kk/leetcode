/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int lengthOfLIS(vector<int>& nums) {
        deque<int> q;
        for (int k : nums) {
            auto it = std::lower_bound(q.begin(), q.end(), k);
            if (it == q.end()) {
                q.push_back(k);
            } else {
                *it = k;
            }
        }

        return q.size();
    }
};
// @lc code=end
