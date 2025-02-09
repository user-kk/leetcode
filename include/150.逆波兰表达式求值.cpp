/*
 * @lc app=leetcode.cn id=150 lang=cpp
 *
 * [150] 逆波兰表达式求值
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        stack<int> val;
        for (auto& s : tokens) {
            if (s == "+") {
                int a = val.top();
                val.pop();
                int b = val.top();
                val.pop();
                val.push(a + b);
            } else if (s == "-") {
                int a = val.top();
                val.pop();
                int b = val.top();
                val.pop();
                val.push(b - a);
            } else if (s == "*") {
                int a = val.top();
                val.pop();
                int b = val.top();
                val.pop();
                val.push(a * b);
            } else if (s == "/") {
                int a = val.top();
                val.pop();
                int b = val.top();
                val.pop();
                val.push(b / a);
            } else {
                val.push(std::stoi(s));
            }
        }
        return val.top();
    }
};
// @lc code=end
