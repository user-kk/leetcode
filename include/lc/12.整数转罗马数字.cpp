/*
 * @lc app=leetcode.cn id=12 lang=cpp
 *
 * [12] 整数转罗马数字
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! 贪心，大于等于哪个就是哪个
    string intToRoman(int num) {
        struct T {
            int v;
            string symbol;
        };

        vector<T> k{
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
            {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
            {5, "V"},    {4, "IV"},   {1, "I"},
        };

        string ret;
        for (auto &[v, sym] : k) {
            while (num >= v) {
                ret.append(sym);
                num -= v;
            }
        }
        return ret;
    }
};
// @lc code=end
