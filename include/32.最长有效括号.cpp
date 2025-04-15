/*
 * @lc app=leetcode.cn id=32 lang=cpp
 *
 * [32] 最长有效括号
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int longestValidParentheses(string_view s) {
        int ret = 0;
        int left_num = 0;  // 当前积累的左括号数
        int dp = 0;        // 以当前位置为结束的字符串的最长有效括号长度
        // 处理左括号少于右括号的情况
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(') {
                left_num++;
            } else {
                if (left_num > 1) {
                    left_num--;
                    dp += 2;
                } else if (left_num == 1) {
                    left_num--;
                    dp += 2;
                    ret = std::max(ret, dp);
                } else {
                    dp = 0;
                }
            }
        }

        // 处理右括号少于左括号的情况
        int right_num = 0;
        dp = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            char c = s[i];
            if (c == ')') {
                right_num++;
            } else {
                if (right_num > 1) {
                    right_num--;
                    dp += 2;
                } else if (right_num == 1) {
                    right_num--;
                    dp += 2;
                    ret = std::max(ret, dp);
                } else {
                    dp = 0;
                }
            }
        }

        return ret;
    }
};
// @lc code=end
