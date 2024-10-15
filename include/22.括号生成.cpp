/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    void generate(vector<string>& ret, int depth, const int n, string& s,
                  int left_num, int right_num) {
        depth++;
        if (depth == 2 * n) {
            if (left_num == n && right_num == n - 1) {
                s[depth - 1] = ')';
                ret.push_back(s);
            }
            return;
        }

        // 放左面
        if (left_num < n) {
            s[depth - 1] = '(';
            generate(ret, depth, n, s, left_num + 1, right_num);
        }

        // 放右面
        if (right_num < left_num) {
            s[depth - 1] = ')';
            generate(ret, depth, n, s, left_num, right_num + 1);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        string s(2 * n, '\0');
        generate(ret, 0, n, s, 0, 0);
        return ret;
    }
};
// @lc code=end
