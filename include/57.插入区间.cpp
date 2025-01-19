/*
 * @lc app=leetcode.cn id=57 lang=cpp
 *
 * [57] 插入区间
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    // left-right: 1-2  3-4 插入a-b
    // 找到第一个right使a<=right,找到最后一个left使left>=b
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        int left = 0;
        int right = intervals.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (intervals[mid][1] >= newInterval[0]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        int left_interval = left;
        if (left_interval == intervals.size()) {
            intervals.push_back(newInterval);
            return intervals;
        }

        left = -1;
        right = intervals.size() - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (intervals[mid][0] <= newInterval[1]) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        int right_internal = left;
        if (right_internal == -1) {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }
        vector<vector<int>> ret;
        ret.reserve(intervals.size() + 1);
        for (int i = 0; i < left_interval; i++) {
            ret.push_back(intervals[i]);
        }

        ret.push_back(vector<int>(
            {std::min(intervals[left_interval][0], newInterval[0]),
             std::max(intervals[right_internal][1], newInterval[1])}));

        for (int i = right_internal + 1; i < intervals.size(); i++) {
            ret.push_back(intervals[i]);
        }
        return ret;
    }
};
// @lc code=end
