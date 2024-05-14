/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */
#include <common.h>

#include <vector>
// @lc code=start
class Solution {
   public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
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
        while (!p.empty()) {
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
                return false;
            }
        }
        return true;
    }
};
// @lc code=end
