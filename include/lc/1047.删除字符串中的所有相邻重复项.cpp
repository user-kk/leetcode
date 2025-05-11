/*
 * @lc app=leetcode.cn id=1047 lang=cpp
 *
 * [1047] 删除字符串中的所有相邻重复项
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    string removeDuplicates(string_view s) {
        deque<char> st;

        for (auto c : s) {
            if (st.empty()) {
                st.push_back(c);
                continue;
            }

            if (c == st.back()) {
                st.pop_back();
            } else {
                st.push_back(c);
            }
        }
        return {st.begin(), st.end()};
    }
};
// @lc code=end
