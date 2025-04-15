/*
 * @lc app=leetcode.cn id=860 lang=cpp
 *
 * [860] 柠檬水找零
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    bool lemonadeChange(vector<int>& bills) {
        int num_5 = 0;
        int num_10 = 0;
        for (auto v : bills) {
            switch (v) {
                case 5: {
                    num_5++;
                    break;
                }
                case 10: {
                    num_10++;
                    if (num_5 > 0) {
                        num_5--;
                    } else {
                        return false;
                    }
                    break;
                }
                case 20: {
                    if (num_10 > 0 && num_5 > 0) {
                        num_10--;
                        num_5--;
                    } else if (num_5 >= 3) {
                        num_5 -= 3;
                    } else {
                        return false;
                    }
                    break;
                }
            }
        }
        return true;
    }
};
// @lc code=end
