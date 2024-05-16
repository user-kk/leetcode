/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    string longestPalindrome(const string& s) {
        string k;
        k.reserve(2 * s.size() + 3);
        k.push_back('^');
        k.push_back('#');
        for (char c : s) {
            k.push_back(c);
            k.push_back('#');
        }
        k.push_back('$');

        // 保存最右回文子串的信息
        int c_index = 1;    // 最右回文中心
        int c_r_index = 1;  // z最右回文最右侧

        // dp[i]以k[i]为中心的最大回文半径 例 #a# dp[1]==2
        vector<int> dp(k.size(), 1);

        // 开头和结尾不用算dp,一定是1，结尾算dp在扩散时会越界
        for (int i = 1; i < k.size() - 1; i++) {
            if (i <= c_r_index) {
                dp[i] = std::min(dp[2 * c_index - i], c_r_index - i + 1);
            }

            while (k[i + dp[i]] == k[i - dp[i]]) {
                dp[i]++;
            }

            if (i + dp[i] - 1 > c_r_index) {
                c_index = i;
                c_r_index = i + dp[i] - 1;
            }
        }

        auto it = std::max_element(dp.begin(), dp.end());
        int center = it - dp.begin();
        int length = *it;
        string ret;
        ret.reserve(length - 1);
        for (int i = center - length + 1; i <= center + length - 1; i++) {
            if (k[i] != '#') {
                ret.push_back(k[i]);
            }
        }

        return ret;
    }
};
// @lc code=end
