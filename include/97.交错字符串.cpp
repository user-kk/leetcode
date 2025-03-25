/*
 * @lc app=leetcode.cn id=97 lang=cpp
 *
 * [97] 交错字符串
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 原始dp[i][j]代表s1取前i个，s2取前j个能组成s3的前i+j个
    // 下面是压缩后的dp
    bool isInterleave(string_view s1, string_view s2, string_view s3) {
        if (s3.size() != s1.size() + s2.size()) {
            return false;
        }
        std::vector<bool> dp(s2.size() + 1, false);
        // 初始化dp
        dp[0] = true;
        for (int i = 1; i < dp.size(); i++) {
            if (s3[i - 1] == s2[i - 1]) {
                dp[i] = true;
            } else {
                break;
            }
        }
        for (int j = 1; j < s1.size() + 1; j++) {
            for (int i = 0; i < dp.size(); i++) {
                if (i == 0) {
                    if (dp[i] && s1[j - 1] == s3[j - 1]) {
                        dp[i] = true;
                    } else {
                        dp[i] = false;
                    }
                    continue;
                }
                if (dp[i] && s3[j + i - 1] == s1[j - 1]) {
                    dp[i] = true;
                } else {
                    dp[i] = false;
                }
                if (dp[i - 1] && s3[j + i - 1] == s2[i - 1]) {
                    dp[i] = true;
                }
            }
        }
        return dp.back();
    }
};
// @lc code=end
