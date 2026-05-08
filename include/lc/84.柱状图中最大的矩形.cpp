/*
 * @lc app=leetcode.cn id=84 lang=cpp
 *
 * [84] 柱状图中最大的矩形
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        //! 和接雨水有点相反，找左右两边第一个比我小的
        //! max(自己高度 * (右边比我小的位置坐标 - 左边比我小的位置坐标))
        vector<int> left(heights.size(), -1);
        vector<int> right(heights.size(), heights.size());

        stack<int> st;  // 放index

        for (int i = 0; i < heights.size(); i++) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                right[st.top()] = i;
                st.pop();
            }

            if (!st.empty()) {
                left[i] = st.top();
            }
            st.push(i);
        }

        int ret = INT_MIN;
        for (int i = 0; i < heights.size(); i++) {
            ret = std::max(ret, heights[i] * (right[i] - left[i] - 1));
        }
        return ret;
    }
};
// @lc code=end
