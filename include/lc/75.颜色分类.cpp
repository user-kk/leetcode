/*
 * @lc app=leetcode.cn id=75 lang=cpp
 *
 * [75] 颜色分类
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    void sortColors(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        int cur = 0;
        while (cur <= r) {
            switch (nums[cur]) {
                case 0: {
                    std::swap(nums[cur], nums[l]);
                    l++;
                    //! 换过来按理说cur不该走，因为不确定换过来的是什么
                    // 但是如果是开头是0这种情况，会导致cur落后于l，这会导致死循环
                    // cur落后于l能确认cur当前的一定是0,所以直接cur++就行
                    if (cur < l) {
                        cur++;
                    }
                    break;
                }
                case 1: {
                    cur++;
                    break;
                }
                case 2: {
                    std::swap(nums[cur], nums[r]);
                    r--;
                    break;
                }
            }
        }
    }
};
// @lc code=end
