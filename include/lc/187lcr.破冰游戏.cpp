/*
 * @lc app=leetcode.cn id=lcr 187 lang=cpp
 *
 */
#include <cstdint>
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 约瑟夫环 , f(n,k)为总人数为n时，删除第k个时，对应人的坐标
    // f(n,k) = (f(n-1)+k) % n
    // 已知 想要求f(1,k) == 0（即幸存者）时对应的那个人的f(n,k)
    int iceBreakingGame(int num, int target) {
        int res = 0;  // f(1,k) == 0
        for (int i = 2; i <= num; i++) {
            res = (res + target) % i;
        }
        return res;
    }
};
// @lc code=end
