/*
 * @lc app=leetcode.cn id=128 lang=cpp
 *
 * [128] 最长连续序列
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    // 找头，如果num-1在nums中，那么他就不是头
    int longestConsecutive(vector<int>& nums) {
        std::unordered_set<int> set(nums.begin(), nums.end());
        int max = 0;
        for (int e : set) {
            if (set.contains(e - 1)) {
                continue;
            } else {
                int count = 1;
                e++;
                while (set.contains(e)) {
                    count++;
                    e++;
                }
                if (count > max) {
                    max = count;
                }
            }
        }
        return max;
    }
};
// @lc code=end
