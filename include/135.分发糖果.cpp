/*
 * @lc app=leetcode.cn id=135 lang=cpp
 *
 * [135] 分发糖果
 */
#include <numeric>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int candy(vector<int>& ratings) {
        vector<int> v(ratings.size(), 1);
        for (int i = 0; i < ratings.size() - 1; i++) {
            if (ratings[i] < ratings[i + 1] && v[i] >= v[i + 1]) {
                v[i + 1] = v[i] + 1;
            }
        }
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1] && v[i] <= v[i + 1]) {
                v[i] = v[i + 1] + 1;
            }
        }
        return std::accumulate(v.begin(), v.end(), 0);
    }
};
// @lc code=end
