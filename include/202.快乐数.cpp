/*
 * @lc app=leetcode.cn id=202 lang=cpp
 *
 * [202] 快乐数
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    bool isHappy(int n) {
        int a[10];
        for (int i = 0; i < 10; i++) {
            a[i] = i * i;
        }
        std::set<int> finish;  // int为平方和

        while (n != 1) {
            int v = 0;
            while (n != 0) {
                v += a[n % 10];
                n = n / 10;
            }
            if (finish.contains(v)) {
                return false;
            }

            finish.insert(v);
            n = v;
        }
        return true;
    }
};
// @lc code=end
