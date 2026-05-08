/*
 * @lc app=leetcode.cn id=274 lang=cpp
 *
 * [274] H 指数
 */
#include <functional>
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 贪心
    int hIndex(vector<int>& citations) {
        std::sort(citations.begin(), citations.end(), std::greater<int>());

        int hindex = 1;
        for (int i = 0; i < citations.size(); i++, hindex++) {
            if (hindex > citations[i]) {
                break;
            }
        }
        return hindex - 1;
    }
};
// @lc code=end
