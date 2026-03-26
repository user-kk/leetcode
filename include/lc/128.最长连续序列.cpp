/*
 * @lc app=leetcode.cn id=128 lang=cpp
 *
 * [128] 最长连续序列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! 找头，如果num-1在nums中，那么他就不是头
    int longestConsecutive(vector<int>& nums) {
        std::unordered_set<int> set(nums.begin(), nums.end());
        int max = 0;
        for (int e : set) {
            if (set.contains(e - 1)) {
                continue;
            } else {
                int count = 1;
                e++;
                while (set.contains(e)) {
                    count++;
                    e++;
                }
                if (count > max) {
                    max = count;
                }
            }
        }
        return max;
    }

    int longestConsecutive2(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        std::unordered_map<int, int> m{};
        int max_len = 1;

        for (auto i : nums) {
            m.insert({i, 0});
        }

        for (auto& [num, cnt] : m) {
            if (cnt != 0) {
                continue;
            }
            int v = num;
            cnt = 1;
            auto it = m.find(v + 1);
            while (it != m.end()) {
                if (it->second != 0) {
                    cnt += it->second;
                    break;
                }

                it->second = 1;
                cnt++;
                v = it->first;
                it = m.find(v + 1);
            }

            max_len = std::max(max_len, cnt);
        }

        return max_len;
    }
};
// @lc code=end
