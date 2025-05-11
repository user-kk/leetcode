/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 *
 * [1143] 最长公共子序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int longestCommonSubsequence(string_view text1, string_view text2) {
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));

        int ret = 0;
        if (text1[0] == text2[0]) {
            dp[0][0] = 1;
            ret = 1;
        }
        for (int i = 1; i < text2.size(); i++) {
            if (dp[0][i - 1] == 1) {
                dp[0][i] = 1;
                continue;
            }
            if (text1[0] == text2[i]) {
                dp[0][i] = 1;
                ret = 1;
            }
        }

        for (int i = 1; i < text1.size(); i++) {
            if (dp[i - 1][0] == 1) {
                dp[i][0] = 1;
                continue;
            }
            if (text1[i] == text2[0]) {
                dp[i][0] = 1;
                ret = 1;
            }
        }

        for (int i = 1; i < text1.size(); i++) {
            for (int j = 1; j < text2.size(); j++) {
                if (text1[i] == text2[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    ret = std::max(ret, dp[i][j]);
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return ret;
    }
};
// @lc code=end
