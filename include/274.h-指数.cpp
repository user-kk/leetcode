/*
 * @lc app=leetcode.cn id=274 lang=cpp
 *
 * [274] H 指数
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int hIndex(vector<int>& citations) {
        std::ranges::sort(citations);
        int n = citations.size();
        for (auto i : citations) {
            if (i >= n) {
                return n;
            }
            n--;
        }
        return 0;
    }
};
// @lc code=end
