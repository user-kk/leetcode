/*
 * @lc app=leetcode.cn id=452 lang=cpp
 *
 * [452] 用最少数量的箭引爆气球
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int findMinArrowShots(vector<vector<int>>& points) {
        std::ranges::sort(points, [](const auto& a, const auto& b) {
            if (a[1] != b[1]) {
                return a[1] < b[1];
            }
            return a[0] < b[0];
        });
        int ret = 1;
        int shot_pos = points[0][1];
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] <= shot_pos && shot_pos <= points[i][1]) {
                continue;
            }

            ret++;
            shot_pos = points[i][1];
        }
        return ret;
    }
};
// @lc code=end
