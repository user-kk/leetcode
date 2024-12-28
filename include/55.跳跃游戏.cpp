/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    bool canJump(vector<int>& nums) {
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
};
// @lc code=end
