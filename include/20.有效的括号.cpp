/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    bool isValid(string& s) {
        stack<char> st;
        for (char c : s) {
            switch (c) {
                case '(': {
                    st.push('(');
                    break;
                }
                case '{': {
                    st.push('{');
                    break;
                }
                case '[': {
                    st.push('[');
                    break;
                }
                case ')': {
                    if (!st.empty() && st.top() == '(') {
                        st.pop();
                        break;
                    }
                    return false;
                }
                case '}': {
                    if (!st.empty() && st.top() == '{') {
                        st.pop();
                        break;
                    }
                    return false;
                }
                case ']': {
                    if (!st.empty() && st.top() == '[') {
                        st.pop();
                        break;
                    }
                    return false;
                }
                default: {
                    break;
                }
            }
        }
        return st.empty();
    }
};
// @lc code=end
