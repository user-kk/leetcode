/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */
#include <climits>
#include "common.h"
// @lc code=start
class Solution {
   public:
    struct T {
        std::unordered_map<char, int> m;
        int count;
        void init(string_view t) {
            for (auto c : t) {
                if (auto it = m.find(c); it != m.end()) {
                    it->second++;
                } else {
                    m[c] = 1;
                }
            }
            count = m.size();
        }

        void push(char c) {
            if (auto it = m.find(c); it != m.end()) {
                it->second--;
                if (it->second == 0) {
                    count--;
                }
            }
        }
        void restore(char c) {
            if (auto it = m.find(c); it != m.end()) {
                it->second++;
                if (it->second == 1) {
                    count++;
                }
            }
        }
        bool success() const { return count == 0; }
    };
    // 滑动窗口模板
    string minWindow(string_view s, string_view t) {
        T q;
        q.init(t);
        int left = 0;
        int min_len = INT_MAX;
        pair<int, int> pos_when_min;

        for (int right = 0; right < s.size(); right++) {
            q.push(s[right]);
            while (q.success()) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    pos_when_min = {left, right};
                }
                q.restore(s[left]);
                left++;
            }
        }

        return min_len == INT_MAX ? ""s
                                  : string{s.begin() + pos_when_min.first,
                                           s.begin() + pos_when_min.second + 1};
    }
};
// @lc code=end
