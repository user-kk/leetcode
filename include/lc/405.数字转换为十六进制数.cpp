/*
 * @lc app=leetcode.cn id=405 lang=cpp
 *
 * [405] 数字转换为十六进制数
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    string toHex(int num) {
        uint32_t k = static_cast<uint32_t>(num);
        if (k == 0) {
            return "0";
        }
        string ret;
        for (int i = 0; i < 8; i++) {
            if (k == 0) {
                break;
            }

            int v = k & 0xF;

            if (v <= 9) {
                ret.push_back(v + '0');
            } else {
                ret.push_back(v - 10 + 'a');
            }

            k = k >> 4;
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};
// @lc code=end
