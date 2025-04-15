/*
 * @lc app=leetcode.cn id=763 lang=cpp
 *
 * [763] 划分字母区间
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> partitionLabels(string_view s) {
        std::array<int, 26> map{};
        std::ranges::fill(map, -1);

        for (int i = 0; i < s.size(); i++) {
            map[s[i] - 'a'] = i;
        }
        vector<int> ret;
        int max = map[s[0] - 'a'];
        int pre = 0;
        for (int i = 0; i < s.size(); i++) {
            if (max == i) {
                ret.push_back(i + 1 - pre);
                pre = i + 1;
                if (i + 1 < s.size()) {
                    max = map[s[i + 1] - 'a'];
                }
            } else {
                max = std::max(max, map[s[i] - 'a']);
            }
        }
        return ret;
    }
};
// @lc code=end
