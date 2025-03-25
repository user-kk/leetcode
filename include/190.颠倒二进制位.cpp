/*
 * @lc app=leetcode.cn id=190 lang=cpp
 *
 * [190] 颠倒二进制位
 */
#include <bitset>
#include "common.h"
// @lc code=start
class Solution {
   public:
    // !!位运算也可以考虑std::bitset
    uint32_t reverseBits(uint32_t n) {
        uint32_t val = 0;

        uint32_t v = 1;
        for (int i = 0; i < 32; i++) {
            val = val | ((n & v) << (31 - i));
            n = n >> 1;
        }
        return val;
    }
};
// @lc code=end
