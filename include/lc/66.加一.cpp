/*
 * @lc app=leetcode.cn id=66 lang=cpp
 *
 * [66] 加一
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> plusOne(vector<int>& digits) {
        deque<int> ret;
        int k = 1;  // 进位
        for (int i = digits.size() - 1; i >= 0; i--) {
            ret.push_front((digits[i] + k) % 10);
            k = (digits[i] + k) / 10;
        }

        if (k == 1) {
            ret.push_front(1);
        }
        return {ret.begin(), ret.end()};
    }
};
// @lc code=end
