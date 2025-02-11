/*
 * @lc app=leetcode.cn id=210 lang=cpp
 *
 * [210] 课程表 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        struct E {
            int k = 0;  // 入度
            std::unordered_set<int> outs;
        };

        vector<E> graph(numCourses);

        queue<int> p;  // 入度为0的课
        for (auto& i : prerequisites) {
            graph[i[1]].outs.insert(i[0]);
            graph[i[0]].k++;
        }

        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].k == 0) {
                p.push(i);
            }
        }

        vector<int> ret;
        while (!p.empty()) {
            ret.emplace_back(p.front());
            for (int i : graph[p.front()].outs) {
                graph[i].k--;
                if (graph[i].k == 0) {
                    p.push(i);
                }
            }
            p.pop();
        }

        for (auto& i : graph) {
            if (i.k != 0) {
                return {};
            }
        }
        return ret;
    }
};
// @lc code=end
