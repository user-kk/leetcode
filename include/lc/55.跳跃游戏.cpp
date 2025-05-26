/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    bool canJump2(vector<int>& nums) {
        int i = 0;
        while (i < nums.size()) {
            while (i < nums.size() - 1 && nums[i] != 0) {
                i++;
            }
            if (i >= nums.size() - 1) {
                return true;
            }
            int len = 0;
            for (int j = i; j < nums.size() - 1 && nums[j] == 0; j++) {
                len++;
            }
            for (int j = i - 1; j >= -1; j--) {
                if (j == -1) {
                    return false;
                }
                if (nums[j] > len) {
                    break;
                }
                len++;
            }
            i = i + len;
        }
        return true;
    }

    bool canJump(vector<int>& nums) {
        if (nums.size() == 1) {
            return true;
        }
        int cost = 1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] < cost) {
                cost++;
            } else {
                cost = 1;
            }
        }
        return cost == 1;
    }
};
// @lc code=end
