/*
 * @lc app=leetcode.cn id=167 lang=cpp
 *
 * [167] 两数之和 II - 输入有序数组
 */
#include <common.h>
namespace {
// @lc code=start
class Solution {
   public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0;
        int r = numbers.size() - 1;
        while (l < r) {
            int v = numbers[l] + numbers[r];
            if (v == target) {
                return {l + 1, r + 1};
            } else if (v < target) {
                l++;
            } else {
                r--;
            }
        }
        return {};
    }
};
// @lc code=end
}  // namespace