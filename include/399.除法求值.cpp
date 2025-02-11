/*
 * @lc app=leetcode.cn id=399 lang=cpp
 *
 * [399] 除法求值
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {
        set<string> key_set;

        for (const auto& i : equations) {
            key_set.insert(i[0]);
            key_set.insert(i[1]);
        }

        map<string, int> name_to_int;

        int count = 0;
        for (const auto& i : key_set) {
            name_to_int.insert({i, count++});
        }

        struct T {
            double val;
            int next;
        };

        vector<T> graph(count, {1, 0});
        for (int i = 0; i < graph.size(); i++) {
            graph[i].next = i;
        }

        auto get_root = [&graph](int start) {
            double cost = 1;
            while (graph[start].next != start) {
                cost *= graph[start].val;
                start = graph[start].next;
            }
            return make_pair(start, cost);
        };

        auto connect = [&get_root, &graph](int a, int b, double cost) {
            auto [root1, cost1] = get_root(a);
            auto [root2, cost2] = get_root(b);
            graph[root1].next = root2;
            graph[root1].val = cost2 * cost / cost1;
        };  // 插入 a->b的边

        for (int i = 0; i < equations.size(); i++) {
            connect(name_to_int[equations[i][0]], name_to_int[equations[i][1]],
                    values[i]);
        }

        vector<double> ret;
        for (auto& i : queries) {
            auto a_it = name_to_int.find(i[0]);
            if (a_it == name_to_int.end()) {
                ret.emplace_back(-1);
                continue;
            }
            auto b_it = name_to_int.find(i[1]);
            if (b_it == name_to_int.end()) {
                ret.emplace_back(-1);
                continue;
            }

            int a = a_it->second;
            int b = b_it->second;
            auto [root1, cost1] = get_root(a);
            auto [root2, cost2] = get_root(b);
            if (root1 != root2) {
                ret.emplace_back(-1);
                continue;
            }

            ret.emplace_back(cost1 / cost2);
        }
        return ret;
    }
};
// @lc code=end
