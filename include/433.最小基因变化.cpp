/*
 * @lc app=leetcode.cn id=433 lang=cpp
 *
 * [433] 最小基因变化
 */
#include <common.h>
#include <string_view>
#include <vector>
// @lc code=start
class Solution {
   public:
    int diff(string_view a, string_view b) {
        int ret = 0;
        for (int i = 0; i < 8; i++) {
            if (a[i] != b[i]) {
                ret++;
            }
        }
        return ret;
    }
    int minMutation(string& startGene, string& endGene, vector<string>& bank) {
        queue<string> q1;
        queue<string> q2;

        q1.push(startGene);
        unordered_map<string, bool> m;
        for (auto& s : bank) {
            m[s] = false;
        }

        int cost = 0;

        while (!q1.empty() || !q2.empty()) {
            while (!q1.empty()) {
                string current = std::move(q1.front());
                q1.pop();
                if (diff(current, endGene) == 0) {
                    return cost;
                }

                for (int i = 0; i < bank.size(); i++) {
                    if (m[bank[i]]) {
                        continue;
                    }
                    if (diff(current, bank[i]) == 1) {
                        q2.push(bank[i]);
                        m[bank[i]] = true;
                    }
                }
            }
            cost++;
            while (!q2.empty()) {
                string current = std::move(q2.front());
                q2.pop();
                if (diff(current, endGene) == 0) {
                    return cost;
                }

                for (int i = 0; i < bank.size(); i++) {
                    if (m[bank[i]]) {
                        continue;
                    }
                    if (diff(current, bank[i]) == 1) {
                        q1.push(bank[i]);
                        m[bank[i]] = true;
                    }
                }
            }
            cost++;
        }
        return -1;
    }
};
// @lc code=end
