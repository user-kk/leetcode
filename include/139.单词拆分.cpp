/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 */
#include "common.h"

#include <string>
#include <vector>
// @lc code=start
class Solution {
   public:
    bool wordBreak(string s, const vector<string>& wordDict) {
        std::unordered_set<std::string_view> dict(wordDict.begin(),
                                                  wordDict.end());

        vector<bool> dp(s.size(), false);
        string_view s_view{s};
        dp[0] = dict.contains(s_view.substr(0, 1));

        for (int i = 1; i < s.size(); i++) {
            for (int j = -1; j < i; j++) {  // j代表分割线前一个元素的坐标

                if (j == -1) {
                    dp[i] = dict.contains(s_view.substr(j + 1, i - j));
                    continue;
                }
                if (dp[i]) {
                    break;
                }
                dp[i] = dp[j] && dict.contains(s_view.substr(j + 1, i - j));
            }
        }
        return dp[s.size() - 1];
    }
};
// @lc code=end
