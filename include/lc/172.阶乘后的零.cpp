/*
 * @lc app=leetcode.cn id=172 lang=cpp
 *
 * [172] 阶乘后的零
 */

// @lc code=start
class Solution {
   public:
    // 找因数为5的，注意像25这样的是5*5
    int trailingZeroes(int n) {
        int ret = 0;
        int k = 5;
        while (n / k != 0) {
            ret += n / k;
            k = k * 5;
        }
        return ret;
    }
};
// @lc code=end
