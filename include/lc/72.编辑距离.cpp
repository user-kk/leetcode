/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int minDistance(const string& word1, const string& word2) {
        // dp:word1的前i个变成word2的前j个的最小次数
        // 如果 word1[i - 1] == word2[j - 1]
        // 第i和第j个相同不用变，word1的前i-1个变成word2的前j-1个
        // 如果不同，则有三种情况
        // 选择把第i个变成第j个 dp[i][j]=dp[i - 1][j - 1] + 1
        // 选择删除第i个,把前i-1个变成前j个 dp[i][j]=dp[i - 1][j] + 1
        // 选择增加一个,把前i个变成前j-1个 dp[i][j]=dp[i][j - 1] + 1
        vector<vector<int>> dp(word1.size() + 1,
                               std::vector<int>(word2.size() + 1, 0));
        for (int i = 1; i <= word1.size(); i++) {
            dp[i][0] = i;
        }
        for (int i = 1; i <= word2.size(); i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min({dp[i - 1][j - 1] + 1, dp[i][j - 1] + 1,
                                         dp[i - 1][j] + 1});
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
// @lc code=end
