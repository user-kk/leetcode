/*
 * @lc app=leetcode.cn id=18 lang=cpp
 *
 * [18] 四数之和
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> fourSum(vector<int>& nums, int t) {
        vector<vector<int>> ret;
        std::ranges::sort(nums);
        for (int i = 0; i < static_cast<int>(nums.size()) - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {  // 过掉重复的数
                continue;
            }
            for (int j = i + 1; j < static_cast<int>(nums.size()) - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {  // 过掉重复的数
                    continue;
                }
                int l = j + 1;
                int r = static_cast<int>(nums.size()) - 1;
                long target = static_cast<long>(t) - (nums[i] + nums[j]);
                while (l < r) {
                    if (static_cast<long>(nums[l]) + nums[r] > target) {
                        r--;
                    } else if (static_cast<long>(nums[l]) + nums[r] < target) {
                        l++;
                    } else {
                        vector v{nums[i], nums[j], nums[l], nums[r]};
                        ret.emplace_back(std::move(v));
                        r--;
                        while (l < r &&
                               nums[r] == nums[r + 1]) {  // 过掉重复的数
                            r--;
                        }
                        l++;
                        while (l < r && nums[l] == nums[l - 1]) {
                            l++;
                        }
                    }
                }
            }
        }
        return ret;
    }
};
// @lc code=end
