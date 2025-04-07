/*
 * @lc app=leetcode.cn id=93 lang=cpp
 *
 * [93] 复原 IP 地址
 */
#include <string>
#include "common.h"
N_B
// @lc code=start
#include <charconv>
    class Solution {
   public:
    vector<string> ret;
    void dfs(string_view s, int depth, long cur_val) {
        if (depth == 5) {
            if (s.empty()) {
                int a = cur_val / 1000'000'000;
                int b = (cur_val % 1000'000'000) / 1000'000;
                int c = (cur_val % 1000'000) / 1000;
                int d = (cur_val) % 1000;

                ret.push_back(std::to_string(a) + '.' + std::to_string(b) +
                              '.' + std::to_string(c) + '.' +
                              std::to_string(d));
            }
            return;
        }
        if (s[0] == '0') {
            dfs(s.substr(1), depth + 1, cur_val * 1000);
            return;
        }

        for (int i = 1; i <= 3; i++) {
            if (s.size() < i) {
                break;
            }
            string_view num_view = s.substr(0, i);
            int num = 0;
            std::from_chars(num_view.data(),
                            num_view.data() + num_view.length(), num);
            if (num > 255) {
                break;
            }
            dfs(s.substr(i), depth + 1, (cur_val * 1000 + num));
        }
    }
    vector<string> restoreIpAddresses(const string& s) {
        dfs(s, 1, 0);
        return ret;
    }
};
// @lc code=end
N_E
