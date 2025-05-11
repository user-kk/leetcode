/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 */

#include "common.h"
namespace {
// 类似于动态规划，从最后一个开始，利用已经算出的结果进行跳转搜索
vector<int> dailyTemperatures(const vector<int>& temperatures) {
    if (temperatures.size() == 1) {
        return {0};
    }
    vector<int> ret(temperatures.size());
    ret[ret.size() - 1] = 0;
    for (int i = temperatures.size() - 2; i >= 0; i--) {
        if (temperatures[i] < temperatures[i + 1]) {
            ret[i] = 1;
            continue;
        } else {
            int cur_i = i + 1;
            while (temperatures[i] >= temperatures[cur_i]) {
                if (ret[cur_i] == 0) {
                    break;
                }
                cur_i = cur_i + ret[cur_i];
            }
            if (temperatures[i] >= temperatures[cur_i]) {
                ret[i] = 0;
                continue;
            }
            ret[i] = cur_i - i;
        }
    }
    return ret;
}

// @lc code=start
class Solution {
   public:
    // 单调栈
    // 找第一个最大的，那么就维护一个递减的单调栈，单调失败时第一个最大的就找到了
    vector<int> dailyTemperatures(const vector<int>& temperatures) {
        vector<int> ret(temperatures.size());
        struct E {
            int v;
            int pos;
        };
        std::stack<E> s;
        s.push({temperatures[0], 0});
        for (int i = 1; i < temperatures.size(); i++) {
            if (!s.empty() && temperatures[i] > s.top().v) {
                ret[s.top().pos] = i - s.top().pos;
                s.pop();
                while (!s.empty() && s.top().v < temperatures[i]) {
                    ret[s.top().pos] = i - s.top().pos;
                    s.pop();
                }
            }
            s.push({temperatures[i], i});
        }
        while (!s.empty()) {
            ret[s.top().pos] = 0;
            s.pop();
        }
        return ret;
    }
};
// @lc code=end
}  // namespace