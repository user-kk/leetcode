/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<string>> groupAnagrams1(vector<string>& strs) {
        auto hash = [](const std::unordered_multiset<char>& s) -> size_t {
            return std::accumulate(s.begin(), s.end(), 0);
        };
        std::unordered_map<std::unordered_multiset<char>,
                           std::vector<std::string>, decltype(hash)>
            m(0, hash);
        for (auto& s : strs) {
            std::unordered_multiset<char> set(s.begin(), s.end());
            if (auto it = m.find(set); it != m.end()) {
                it->second.push_back(s);
            } else {
                m.emplace(std::move(set), std::vector<string>{s});
            }
        }
        vector<vector<string>> ret;
        ret.reserve(m.size());

        for (auto& it : m) {
            ret.emplace_back(std::move(it.second));
        }
        return ret;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> m;
        for (auto& s : strs) {
            string k = s;
            std::sort(k.begin(), k.end());
            if (auto it = m.find(k); it != m.end()) {
                it->second.push_back(s);
            } else {
                m.emplace(std::move(k), std::vector<string>{s});
            }
        }
        vector<vector<string>> ret;
        ret.reserve(m.size());

        for (auto& it : m) {
            ret.emplace_back(std::move(it.second));
        }
        return ret;
    }
};
// @lc code=end
