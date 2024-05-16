/*
 * @lc app=leetcode.cn id=238 lang=cpp
 *
 * [238] 除自身以外数组的乘积
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> ret(nums.size(), 1);
        int l = 1;
        int r = 1;
        for (int i = 1; i < nums.size(); i++) {
            l = l * nums[i - 1];
            ret[i] = l;
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            r = r * nums[i + 1];
            ret[i] *= r;
        }
        return ret;
    }
};
// @lc code=end
