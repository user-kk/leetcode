/*
 * @lc app=leetcode.cn id=6 lang=cpp
 *
 * [6] Z 字形变换
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    string convert(const string& s, int numRows) {
        if (numRows == 1) {
            return s;
        }

        vector<string> rets(numRows);
        bool is_down = true;
        int pos = 0;
        for (char c : s) {
            rets[pos].push_back(c);
            if (is_down) {
                if (pos == numRows - 1) {
                    pos--;
                    is_down = false;
                } else {
                    pos++;
                }
            } else {
                if (pos == 0) {
                    pos++;
                    is_down = true;
                } else {
                    pos--;
                }
            }
        }

        string ret;
        for (auto& s : rets) {
            ret.append(s);
        }
        return ret;
    }
};
// @lc code=end
