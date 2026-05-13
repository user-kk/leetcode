/*
 * @lc app=leetcode.cn id=201 lang=cpp
 *
 * [201] 数字范围按位与
 */
#include <bitset>
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 本质:找公共前缀
    int rangeBitwiseAnd(int left, int right) {
        // 谁大谁把最右边的1置0，直至相等

        while (left != right) {
            if (left < right) {
                right = right & (right - 1);
            } else {
                left = left & (left - 1);
            }
        }

        return left;
    }
};
// @lc code=end
