/*
 * @lc app=leetcode.cn id=503 lang=cpp
 *
 * [503] 下一个更大元素 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        vector<int> ret(nums.size(), -1);
        for (int i = (int)nums.size() - 1; i >= 0; i--) {
            while (!st.empty() && st.top() <= nums[i]) {
                st.pop();
            }
            st.push(nums[i]);
        }
        for (int i = (int)nums.size() - 1; i >= 0; i--) {
            while (!st.empty() && st.top() <= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                ret[i] = st.top();
            }
            st.push(nums[i]);
        }
        return ret;
    }
};
// @lc code=end
