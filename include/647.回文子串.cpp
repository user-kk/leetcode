/*
 * @lc app=leetcode.cn id=647 lang=cpp
 *
 * [647] 回文子串
 */
#include <common.h>

// @lc code=start
class Solution {
   public:
    int countSubstrings(const string& s) {
        // 处理字符串，^和$作为哨兵，保证算最大回文时不会越界，因为'^'!='$'
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

        int ret = 0;

        // 开头和结尾不用算dp,一定是1，结尾算dp在扩散时会越界
        for (int i = 1; i < k.size() - 1; i++) {
            if (i <= c_r_index) {
                dp[i] = std::min(dp[2 * c_index - i], c_r_index - i + 1);
            }

            while (k[i + dp[i]] == k[i - dp[i]]) {
                dp[i]++;
            }
            // dp[i]-1 是回文字符串的总长
            // ((dp[i]-1)+1)/2是以k[i]为中心有多少个字符串
            ret += dp[i] / 2;

            // 更新最右回文子串的信息
            if (i + dp[i] - 1 > c_r_index) {
                c_index = i;
                c_r_index = i + dp[i] - 1;
            }
        }
        return ret;
    }
};
// @lc code=end
