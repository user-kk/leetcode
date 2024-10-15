/*
 * @lc app=leetcode.cn id=438 lang=cpp
 *
 * [438] 找到字符串中所有字母异位词
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    vector<int> findAnagrams(const string& s, const string& p) {
        struct T {
            int current;
            int all;
        };
        std::unordered_map<char, T> m;
        int len = p.size();
        int count = 0;
        for (char c : p) {
            if (auto i = m.find(c); i != m.end()) {
                i->second.all++;
            } else {
                m.insert({c, T{0, 1}});
            }
        }

        // 滑动窗口[i,j)
        int i = 0;
        int j = 0;
        vector<int> ret;
        bool clear = true;

        for (int k = 0; k < s.size(); k++) {
            if (auto it = m.find(s[k]); it != m.end()) {
                clear = false;
                it->second.current++;
                j++;
                count++;
                if (it->second.current == it->second.all) {
                    if (count == len) {
                        ret.push_back(j - len);
                        // 缩小一格
                        m[s[i]].current--;
                        i++;
                        count--;
                    }
                } else if (it->second.current > it->second.all) {
                    while (s[i] != s[k]) {
                        // 缩小一格
                        m[s[i]].current--;
                        i++;
                        count--;
                    }
                    // 缩小一格
                    m[s[i]].current--;
                    i++;
                    count--;
                }
            } else {
                i = k + 1;
                j = k + 1;
                if (!clear) {
                    count = 0;
                    for (auto& m_it : m) {
                        m_it.second.current = 0;
                    }
                    clear = true;
                }
            }
        }
        return ret;
    }
};
// @lc code=end
