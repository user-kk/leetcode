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

        vector<bool> dp(s.size() + 1, false);
        string_view s_view{s};
        dp[0] = true;  // dp[i]代表前i个字符能被拆分

        // 定义新引入的字符串为s[j->i],左闭右闭
        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j <= i; j++) {  // j代表分割线前一个元素的坐标

                if (dict.contains(s_view.substr(j, i - j + 1)) && dp[j]) {
                    dp[i + 1] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
// @lc code=end