/*
 * @lc app=leetcode.cn id=373 lang=cpp
 *
 * [373] 查找和最小的 K 对数字
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> kSmallestPairs(vector<int>& num1, vector<int>& num2,
                                       int k) {
        //! 当优先队列弹出a[i]和b[j]时
        //! 只需向队列中加入a[i+1],b[j] 和 a[i],b[j+1]即可
        //! 但这样可能会出现重复值,比如出现3,3和2,4时，3,4被填入了两遍
        //! 因为其他元素必然大于min(a[i+1]+b[j],a[i]+b[j+1])
        struct T {
            int i;
            int j;
            auto operator<=>(const T&) const = default;
        };
        auto hash = [](const T& a) {
            return std::hash<int>{}(a.i) ^ std::hash<int>{}(a.j);
        };
        unordered_set<T, decltype(hash)> set;

        auto cmp = [&num1, &num2](const T& a, const T& b) {
            return num1[a.i] + num2[a.j] > num1[b.i] + num2[b.j];
        };

        priority_queue<T, vector<T>, decltype(cmp)> q(cmp);
        q.push({0, 0});

        vector<vector<int>> ret;
        set.insert({0, 0});

        while (ret.size() < k) {
            auto t = q.top();
            q.pop();
            ret.push_back({num1[t.i], num2[t.j]});

            if (t.i + 1 < num1.size() && !set.contains({t.i + 1, t.j})) {
                q.push({t.i + 1, t.j});
                set.insert({t.i + 1, t.j});
            }

            if (t.j + 1 < num2.size() && !set.contains({t.i, t.j + 1})) {
                q.push({t.i, t.j + 1});
                set.insert({t.i, t.j + 1});
            }
        }

        return ret;
    }
};
// @lc code=end
