/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 */
// clang-format off
// 背包模版
// 背包问题：dp[i] 钱数为i时的最优解 i从0开始到n
// 因为01背包必须记录每个买没买，所以外层循环必然是商品
// 完全背包则不需要记录，所以外层循环可以正常为钱数i,内层循环则是遍历每一个商品尝试购买一次
// 因为dp[i-商品价格]已经求得了最优解,所以dp[i] = 在每个商品中最优的dp[i-商品价格]+商品价值
//
// 因为01背包是依赖于前面的值dp[a]而更新后面的值dp[b](a<b)
// 但是每一轮商品只能买一次，所以在本轮的dp[c](c>b)不能依赖于dp[b](因为dp[b]已经买过了)所以要从后往前遍历
// !还要注意新一轮的值还需要和上一轮的比一下确定最终值
//
// 无限背包的遍历顺序有两种，
// 一种是物品在外，这种适合于组合数，即购买顺序不会有1,2，只会有2,1(购买1物品的时候不会考虑2物品，购买2物品的时候才会考虑1物品)
// 另一种是钱在外，这种1,2和2,1会被考虑两次，当做两次来计算，所以适合于排列数，即最后的结果和购买顺序有关
// clang-format on

#include "common.h"
#include <numeric>
// @lc code=start
class Solution {
   public:
    bool canPartition(vector<int>& nums) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1) {
            return false;
        }
        int target = sum / 2;

        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int num : nums) {
            for (int i = target; i >= 0; i--) {
                if (dp[i]) {
                    if (i + num == target) {
                        return true;
                    } else if (i + num < target) {
                        dp[i + num] = true;
                    }
                }
            }
        }
        return false;
    }
};
// @lc code=end
