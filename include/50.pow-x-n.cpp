/*
 * @lc app=leetcode.cn id=50 lang=cpp
 *
 * [50] Pow(x, n)
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 利用2进制可以快速得知n次幂的递归拆分
    // 例如x的11次幂 11:1011 x^8 * x^2
    double myPow(double x, int64_t n) {
        if (n < 0) {
            n = -n;
            x = 1.0 / x;
        }

        double ret = 1;

        while (n != 0) {
            if ((n & 1) == 1) {
                ret *= x;
            }
            x = x * x;
            n = n >> 1;
        }
        return ret;
    }
};
// @lc code=end
