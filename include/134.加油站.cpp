/*
 * @lc app=leetcode.cn id=134 lang=cpp
 *
 * [134] 加油站
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    //! 贪心
    //! a车站一直走走到了b车站(假设没走到一圈)，那么ab之间的车站(包括b)也无法走到b
    //! 假设a->c->d->b
    //! 走到c时一定是正收益(要不然没法走到d)，d有c的正收益的帮助仍无法走到终点，那么从d开始走一定无法走到终点
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        vector<int> val(gas.size());

        for (int i = 0; i < gas.size(); i++) {
            val[i] = gas[i] - cost[i];
        }

        auto it = std::ranges::find_if(val, [](int k) { return k >= 0; });
        if (it == val.end()) {
            return -1;
        }

        int i = it - val.begin();

        while (i < val.size()) {
            int j = i;
            int current = 0;
            do {
                current += val[j % val.size()];
                j++;
            } while (j % val.size() != i && current >= 0);

            if (j % val.size() == i && current >= 0) {
                return i;
            }
            if (j >= val.size()) {
                return -1;
            }
            i = j;
        }
        return -1;
    }
};
// @lc code=end
