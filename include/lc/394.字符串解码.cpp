/*
 * @lc app=leetcode.cn id=394 lang=cpp
 *
 * [394] 字符串解码
 */
#include <string_view>
#include "common.h"
// @lc code=start
class Solution {
   public:
    string decodeString(string_view s) {
        struct T {
            string repeat_num;
            string s;
            bool repeat_end = false;
        };
        stack<T> st;
        string ret;
        for (char c : s) {
            if (c >= '0' && c <= '9') {
                if (st.empty() || st.top().repeat_end == true) {
                    st.push(T{});
                    st.top().repeat_num.push_back(c);
                } else if (st.top().repeat_end == false) {
                    st.top().repeat_num.push_back(c);
                }
            } else if (c == '[') {
                st.top().repeat_end = true;
                continue;
            } else if (c >= 'a' && c <= 'z') {
                if (st.empty()) {
                    ret.push_back(c);
                } else {
                    st.top().s.push_back(c);
                }
            } else if (c == ']') {
                T t = std::move(st.top());
                st.pop();
                int n = std::stoi(t.repeat_num);
                if (st.empty()) {
                    for (int i = 0; i < n; i++) {
                        ret.append(t.s);
                    }
                } else {
                    for (int i = 0; i < n; i++) {
                        st.top().s.append(t.s);
                    }
                }
            }
        }
        return ret;
    }
};
// @lc code=end
