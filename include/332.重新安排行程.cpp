/*
 * @lc app=leetcode.cn id=332 lang=cpp
 *
 * [332] 重新安排行程
 */
#include <common.h>
N_B
    // @lc code=start
    class Solution {
   public:
    unordered_map<string, map<string, int>> m;
    int tickets_num;
    vector<string> path;

    bool dfs(const string& cur, int use_ticket_num) {
        if (use_ticket_num == tickets_num) {
            return true;
        }

        for (auto& [next, have] : m[cur]) {
            if (have == 0) {
                continue;
            }
            path.push_back(next);
            have--;
            if (dfs(next, use_ticket_num + 1)) {
                return true;
            }
            have++;
            path.pop_back();
        }
        return false;
    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& i : tickets) {
            if (auto it = m.find(i[0]); it != m.end()) {
                if (auto it2 = it->second.find(i[1]); it2 != it->second.end()) {
                    it2->second++;
                } else {
                    it->second.insert({i[1], 1});
                }
            } else {
                m.insert({i[0], std::map<string, int>{{i[1], 1}}});
            }
        }
        tickets_num = tickets.size();
        path.push_back("JFK");
        dfs("JFK", 0);

        return path;
    }
};
// @lc code=end
N_E
