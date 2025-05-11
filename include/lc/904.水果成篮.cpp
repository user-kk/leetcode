/*
 * @lc app=leetcode.cn id=904 lang=cpp
 *
 * [904] 水果成篮
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int totalFruit(vector<int>& fruits) {
        int ret = 0;
        int left = 0;
        int right = 0;

        int a = -1;
        int b = -1;
        int cur = 0;
        int cur_type = -1;
        int new_left = -1;

        while (right < fruits.size()) {
            while (right < fruits.size()) {
                if (a == -1) {
                    cur++;
                    a = fruits[right];
                    cur_type = a;
                    new_left = right;
                } else if (fruits[right] == a) {
                    if (fruits[right] != cur_type) {
                        cur_type = fruits[right];
                        new_left = right;
                    }
                    cur++;
                } else if (b == -1) {
                    cur++;
                    b = fruits[right];
                    cur_type = b;
                    new_left = right;
                } else if (fruits[right] == b) {
                    if (fruits[right] != cur_type) {
                        cur_type = fruits[right];
                        new_left = right;
                    }
                    cur++;
                } else {
                    break;
                }
                right++;
            }

            ret = std::max(ret, cur);

            cur = cur - (new_left - left);
            left = new_left;
            if (cur_type == a) {
                b = -1;
            } else {
                a = -1;
            }
        }
        return ret;
    }
};
// @lc code=end
