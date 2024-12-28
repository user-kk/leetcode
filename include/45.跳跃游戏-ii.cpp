/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    int jump1(vector<int>& nums) {  // O(n2)
        if (nums.size() == 1) {
            return 0;
        }
        int target = nums.size() - 1;
        int ret = 0;
        while (target != 0) {
            int next_target = target;
            for (int i = target - 1; i >= 0; i--) {
                if (i + nums[i] >= target) {
                    next_target = i;
                }
            }
            target = next_target;
            ret++;
        }

        return ret;
    }
    int jump(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        int cur = 0;
        int ret = 0;
        // 贪心：在下一步能到达的范围中选择能够到达最远的那一个
        // 这个是最优的，因为其他的选项所能够到达的范围最远的那一个都能到达
        while (cur < nums.size() - 1) {
            int next = cur;
            int d = INT_MIN;

            //! 能直接到最后就不用选择了
            if (cur + nums[cur] >= nums.size() - 1) {
                ret++;
                return ret;
            }
            for (int i = cur + 1; i <= cur + nums[cur]; i++) {
                if (i + nums[i] >= d) {
                    d = i + nums[i];
                    next = i;
                }
            }
            cur = next;
            ret++;
        }

        return ret;
    }
};
// @lc code=end
