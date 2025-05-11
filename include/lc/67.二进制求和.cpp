/*
 * @lc app=leetcode.cn id=67 lang=cpp
 *
 * [67] 二进制求和
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    string addBinary(string& a, string& b) {
        int a_len = a.size();
        int b_len = b.size();
        int len = std::max(a_len, b_len);

        string ret;
        ret.reserve(len + 1);

        int k = 0;  // 进位

        for (int i = 0; i < len; i++) {
            int a_i =
                a_len - 1 - i >= 0 ? (a[a_len - 1 - i] == '0' ? 0 : 1) : 0;
            int b_i =
                b_len - 1 - i >= 0 ? (b[b_len - 1 - i] == '0' ? 0 : 1) : 0;

            int val = a_i + b_i + k;
            k = 0;
            switch (val) {
                case 0: {
                    ret.push_back('0');
                    break;
                }
                case 1: {
                    ret.push_back('1');
                    break;
                }
                case 2: {
                    ret.push_back('0');
                    k = 1;
                    break;
                }
                default: {
                    ret.push_back('1');
                    k = 1;
                    break;
                }
            }
        }
        if (k == 1) {
            ret.push_back('1');
        }
        std::ranges::reverse(ret);
        return ret;
    }
};
// @lc code=end
