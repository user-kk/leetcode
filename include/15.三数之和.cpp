/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    // 另一种滑动窗口，普通的滑动窗口是区间和，这个是两数的和
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        std::ranges::sort(nums);
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i >= 1 && nums[i] == nums[i - 1]) {  // 过掉重复的数
                continue;
            }
            int l = i + 1;
            int r = nums.size() - 1;
            while (l < r) {
                if (nums[l] + nums[r] > -nums[i]) {
                    r--;
                } else if (nums[l] + nums[r] < -nums[i]) {
                    l++;
                } else {
                    vector v{nums[i], nums[l], nums[r]};
                    ret.emplace_back(std::move(v));
                    r--;
                    while (l < r && nums[r] == nums[r + 1]) {  // 过掉重复的数
                        r--;
                    }
                    l++;
                    while (l < r && nums[l] == nums[l - 1]) {
                        l++;
                    }
                }
            }
        }
        return ret;
    }
};
// @lc code=end
