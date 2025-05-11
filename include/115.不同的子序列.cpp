/*
 * @lc app=leetcode.cn id=115 lang=cpp
 *
 * [115] 不同的子序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int numDistinct(string_view s, string_view t) {
        vector<vector<int>> dp(s.size(), vector<int>(t.size(), 0));
        if (s.size() < t.size()) {
            return 0;
        }
        dp[0][0] = s[0] == t[0] ? 1 : 0;

        for (int i = 1; i < t.size(); i++) {
            if (s[i] != t[i]) {
                dp[i][i] = 0;
            } else {
                dp[i][i] = dp[i - 1][i - 1];
            }
        }

        for (int i = 1; i < s.size(); i++) {
            if (s[i] != t[0]) {
                dp[i][0] = dp[i - 1][0];
            } else {
                dp[i][0] = dp[i - 1][0] + 1;
            }
        }

        for (int i = 2; i < s.size(); i++) {
            for (int j = 1; j < i && j < t.size(); j++) {
                if (s[i] != t[j]) {
                    // 不等时直接继承正上的计数,当做s[i]不存在
                    dp[i][j] = dp[i - 1][j];
                } else {
                    if (static_cast<long long>(dp[i - 1][j - 1]) +
                            dp[i - 1][j] <=
                        INT_MAX) {  // 防止溢出
                        //!!
                        //!等时，s[i]可以使用(计数为左上)，也可以不使用(计数为正上)
                        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                    }
                }
            }
        }
        return dp[s.size() - 1][t.size() - 1];
    }
};
// @lc code=end
