/*
 * @lc app=leetcode.cn id=137 lang=cpp
 *
 * [137] 只出现一次的数字 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! 看成是一个具有三个档位的开关，每次碰到1会改变档位，碰到0不变
    //! 这个开关有三个档位，所以用两个数的对应的位来模拟，由这个写真值表
    // !最后观察这个开关的档位，必然不是第0档就是第1档，根据这个计算真值表得到最后结果
    //! 利用真值表来积累每一个对应位的和，用真值表模拟一个模三的加法
    //! 对于最后结果的对应位来说必然是积累的值模3,模三运算也用真值表模拟
    int singleNumber(vector<int>& nums) {
        int a = 0;
        int b = 0;
        for (auto c : nums) {
            //! 注意不能写a= b=,因为第一步会改a
            // ! b就不对了
            int t1 = ((~a) & b & c) | (a & (~b) & (~c));
            int t2 = ((~a) & (~b) & c) | ~a & (b ^ c);
            a = t1;
            b = t2;
        }
        return b;
    }
};
// @lc code=end
