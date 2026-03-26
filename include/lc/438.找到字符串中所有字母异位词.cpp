/*
 * @lc app=leetcode.cn id=438 lang=cpp
 *
 * [438] 找到字符串中所有字母异位词
 */
#include <algorithm>
#include <unordered_map>
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> findAnagrams(const string& s, const string& p) {
        struct T {
            std::array<int, 26> map{};
            int count = 0;
            void init(string_view t) {
                std::ranges::fill(map, INT_MIN);
                count = t.size();
                for (char c : t) {
                    if (map[c - 'a'] == INT_MIN) {
                        map[c - 'a'] = 0;
                    }
                    map[c - 'a']++;
                }
            }
            bool success() const { return count == 0; }
            void push(char c) {
                if (map[c - 'a'] == INT_MIN) {
                    return;
                }
                if (map[c - 'a'] > 0) {
                    count--;
                }

                map[c - 'a']--;
            }
            void restore(char c) {
                if (map[c - 'a'] == INT_MIN) {
                    return;
                }
                if (map[c - 'a'] >= 0) {
                    count++;
                }
                map[c - 'a']++;
            }
        };
        T t{};
        t.init(p);
        int left = 0;
        vector<int> ret;
        for (int right = 0; right < s.size(); right++) {
            t.push(s[right]);
            while (t.success()) {
                if (right - left + 1 == p.size()) {
                    ret.push_back(left);
                }

                t.restore(s[left]);
                left++;
            }
        }
        return ret;
    }
};
// @lc code=end
