/*
 * @lc app=leetcode.cn id=56 lang=cpp
 *
 * [56] 合并区间
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](auto& v1, auto& v2) {
            if (v1[0] != v2[0]) {
                return v1[0] < v2[0];
            }
            return v1[1] < v2[1];
        });
        vector<vector<int>> ret;
        ret.push_back(intervals[0]);
        for (size_t i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= ret.back()[1]) {
                if (intervals[i][1] <= ret.back()[1]) {
                    continue;
                }
                ret.back() = std::vector<int>{ret.back()[0], intervals[i][1]};
            } else {
                ret.push_back(intervals[i]);
            }
        }
        return ret;
    }
};
// @lc code=end
