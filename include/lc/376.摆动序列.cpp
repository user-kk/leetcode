/*
 * @lc app=leetcode.cn id=376 lang=cpp
 *
 * [376] 摆动序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int wiggleMaxLength(vector<int>& nums) {
        switch (nums.size()) {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2: {
                if (nums[0] == nums[1]) {
                    return 1;
                } else {
                    return 2;
                }
            }

            default:
                break;
        }
        int i = 1;
        for (i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[0]) {
                break;
            }
        }
        if (i == nums.size()) {
            return 1;
        }

        int ret = 1;
        enum D { UP, DOWN };

        D d = nums[0] > nums[i] ? DOWN : UP;

        while (i < nums.size()) {
            if (d == UP) {
                for (; i < nums.size() && nums[i] >= nums[i - 1]; i++) {
                };
                if (i == nums.size()) {
                    return ret + 1;
                }
                ret++;
                d = DOWN;
            } else {
                for (; i < nums.size() && nums[i] <= nums[i - 1]; i++) {
                };
                if (i == nums.size()) {
                    return ret + 1;
                }
                ret++;
                d = UP;
            }
        }
        return -1;
    }
};
// @lc code=end
