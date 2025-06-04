/*
 * @lc app=leetcode.cn id=881 lang=cpp
 *
 * [881] 救生艇
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int numRescueBoats(vector<int>& people, int limit) {
        std::sort(people.begin(), people.end());
        int ret = 0;
        int l = 0;
        int r = people.size() - 1;
        while (l < r) {
            if (people[l] + people[r] <= limit) {
                ret++;
                l++;
                r--;
            } else {
                ret++;
                r--;
            }
        }

        if (l == r) {
            ret++;
        }
        return ret;
    }
};
// @lc code=end
