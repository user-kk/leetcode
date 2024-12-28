/*
 * @lc app=leetcode.cn id=131 lang=cpp
 *
 * [131] 分割回文串
 */
#include <common.h>

#include <string_view>
namespace {

// @lc code=start
class Solution {
   public:
    vector<vector<string>> ret;
    vector<string> t;
    vector<vector<bool>> is_palindrome;

    bool is_success(int begin, int end) {  // 是否为回文
        return is_palindrome[begin][end];
    }

    void dfs(const string& s, int begin, int len) {
        if (begin == s.size()) {
            ret.push_back(t);
            return;
        }
        if (begin + len > s.size()) {
            return;
        }
        // 切
        if (is_success(begin, begin + len - 1)) {
            t.emplace_back(s.begin() + begin, s.begin() + begin + len);
            dfs(s, begin + len, 1);
            t.pop_back();
        }

        // 不切
        dfs(s, begin, len + 1);
    }

    vector<vector<string>> partition(string& s) {
        build(s);
        dfs(s, 0, 1);
        return ret;
    }

    void build(string& s) {
        int n = s.size();
        is_palindrome.assign(n, vector<bool>(n, true));
        for (int i = 1; i < n; i++) {
            if (s[i - 1] != s[i]) {
                is_palindrome[i - 1][i] = false;
            }
        }
        // 按斜线遍历
        for (int i = 2; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (!is_palindrome[j - i + 1][j - 1]) {
                    is_palindrome[j - i][j] = false;
                    continue;
                }
                if (s[j - i] != s[j]) {
                    is_palindrome[j - i][j] = false;
                    continue;
                }
            }
        }
    }
};
// @lc code=end
}  // namespace
