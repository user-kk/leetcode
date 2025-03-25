/*
 * @lc app=leetcode.cn id=191 lang=cpp
 *
 * [191] 位1的个数
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int hammingWeight(int n) {
        uint v = 1;
        int ret = 0;
        for (int i = 0; i < 32; i++) {
            if ((n & v) == 1) {
                ret++;
            }
            n = n >> 1;
        }
        return ret;
    }
};
// @lc code=end
