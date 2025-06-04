/*
 * @lc app=leetcode.cn id=621 lang=cpp
 *
 * [621] 任务调度器
 */
#include <algorithm>
#include <unordered_map>
#include "common.h"
// @lc code=start
class Solution {
   public:
    int leastInterval(vector<char>& tasks, int n) {
        std::unordered_map<char, int> m;
        for (char c : tasks) {
            if (auto it = m.find(c); it != m.end()) {
                it->second++;
            } else {
                m.insert({c, 1});
            }
        }

        int max_v = 0;

        int max_cnt = 0;
        int sum = 0;

        for (auto [c, i] : m) {
            max_v = std::max(max_v, i);
        }

        for (auto [c, i] : m) {
            sum += i;
            if (i == max_v) {
                max_cnt++;
            }
        }
        // 那个构造出来的调度图的最后一行不需要完整执行完，所以是(max_v-1)*(n+1)+max_cnt
        return std::max((max_v - 1) * (n + 1) + max_cnt, sum);
    }
};
// @lc code=end
