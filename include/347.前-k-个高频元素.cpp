/*
 * @lc app=leetcode.cn id=347 lang=cpp
 *
 * [347] 前 K 个高频元素
 */
#include <common.h>

#include <queue>
// @lc code=start
class Solution {
   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (auto num : nums) {
            if (auto it = m.find(num); it != nullptr) {
                it->second++;
            } else {
                m.insert({num, 1});
            }
        }
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        };

        std::priority_queue<pair<int, int>, vector<pair<int, int>>,
                            decltype(cmp)>
            q;
        for (auto [val, count] : m) {
            q.emplace(val, count);
        }

        vector<int> ret;
        ret.reserve(k);
        for (int i = 0; i < k; i++) {
            ret.push_back(q.top().first);
            q.pop();
        }
        return ret;
    }
};
// @lc code=end
