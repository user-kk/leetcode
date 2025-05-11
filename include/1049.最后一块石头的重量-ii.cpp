/*
 * @lc app=leetcode.cn id=1049 lang=cpp
 *
 * [1049] 最后一块石头的重量 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! 看成最后一块石头的重量=为每一块石头添加正号或负号的求和
    //! 已知a+b=sum,求min(a-b)=min(sum-2*b)=sum-2*max(b)且a>b,所以b是最接近于sum/2且小于sum/2;
    int lastStoneWeightII(vector<int>& stones) {
        int sum = std::accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;
        std::vector<int> dp(target + 1, 0);
        for (int stone : stones) {
            for (int i = target; i >= 0; i--) {
                if (i - stone >= 0) {
                    dp[i] = std::max(dp[i], dp[i - stone] + stone);
                }
            }
        }

        return sum - 2 * dp[target];
    }
};
// @lc code=end
