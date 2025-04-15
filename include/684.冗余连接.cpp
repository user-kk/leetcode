/*
 * @lc app=leetcode.cn id=684 lang=cpp
 *
 * [684] 冗余连接
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    class DisjointSet {
       public:
        explicit DisjointSet(size_t n) {
            _v.resize(n);
            for (int i = 0; i < n; i++) {
                _v[i] = i;
            }
        }

        bool has_common_root(int a, int b) {
            return get_root(a) == get_root(b);
        }

        bool bind(int a, int b) {
            int a_root = get_root(a);
            int b_root = get_root(b);
            if (a_root == b_root) {
                return false;
            }

            _v[a_root] = b_root;
            return true;
        }

        int get_root(int a) {
            while (_v[a] != a) {
                a = _v[a];
            }
            return a;
        }

       private:
        vector<int> _v;
    };
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DisjointSet s{edges.size()};
        for (auto& e : edges) {
            if (!s.bind(e[0]-1, e[1]-1)) {
                return e;
            }
        }
        return {};
    }
};
// @lc code=end
