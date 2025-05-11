/*
 * @lc app=leetcode.cn id=474 lang=cpp
 *
 * [474] 一和零
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        struct T {
            int num_0;
            int num_1;
        };
        vector<T> infos;
        infos.reserve(strs.size());

        for (auto& s : strs) {
            T t{0, 0};
            for (char c : s) {
                c == '0' ? ++t.num_0 : ++t.num_1;
            }
            infos.push_back(t);
        }
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (T info : infos) {
            for (int i = m; i >= info.num_0; i--) {
                for (int j = n; j >= info.num_1; j--) {
                    dp[i][j] = std::max(dp[i][j],
                                        dp[i - info.num_0][j - info.num_1] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
// @lc code=end
