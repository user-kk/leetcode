/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! 雨水类问题都是小的继续走
    int maxArea(vector<int>& height) {
        int ret = INT_MIN;
        int l_index = 0;
        int r_index = height.size() - 1;
        while (l_index < r_index) {
            if (height[l_index] < height[r_index]) {
                ret = std::max(ret, (r_index - l_index) * height[l_index]);
                l_index++;
            } else {
                ret = std::max(ret, (r_index - l_index) * height[r_index]);
                r_index--;
            }
        }
        return ret;
    }
};
// @lc code=end
