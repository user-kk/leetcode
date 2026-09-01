/*
 * @lc app=leetcode.cn id=115 lang=cpp
 *
 * [115] 不同的子序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:  // t作为行s作为列
    int numDistinct(string_view s, string_view t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        if (s.size() < t.size()) {
            return 0;
        }

        for (int i = 0; i <= s.size(); i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (i < j) {
                    dp[i][j] = 0;
                    continue;
                }

                if (s[i - 1] == t[j - 1]) {
                    if (static_cast<long>(dp[i - 1][j - 1]) + dp[i - 1][j] <=
                        INT_MAX) {
                        //! 例 s=raa t=ra,可以让ra和ra匹配，也可以让r_a和ra匹配
                        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                    }

                } else {
                    // 例 s=rab t=ra,只能让ra匹配
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[s.size()][t.size()];
    }
};

// @lc code=end
