/*
 * @lc app=leetcode.cn id=402 lang=cpp
 *
 * [402] 移掉 K 位数字
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    string removeKdigits(string_view num, int k) {
        // 从左往右找第一个递减的左侧即是被删除的那个 12342 删除4

        deque<char> q;
        int count = 0;

        for (char c : num) {
            while (count < k && !q.empty() && q.back() > c) {
                q.pop_back();
                count++;
            }
            q.push_back(c);
        }
        while (count < k) {
            q.pop_back();
            count++;
        }

        // 去前导零
        auto it =
            std::find_if(q.begin(), q.end(), [](char c) { return c != '0'; });
        if (it == q.end()) {
            return "0";
        }
        return {it, q.end()};
    }
};
// @lc code=end
