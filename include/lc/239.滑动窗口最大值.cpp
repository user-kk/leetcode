/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */
#include "common.h"
// @lc code=start
class Solution {
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        struct T {
            int v;
            int index;
        };

        struct MyDp {
            explicit MyDp(int k) : k(k) {};
            int k;
            std::deque<T> dp;
            void push(int val, int index) {
                //! 从队首开始清除过期的(一直在往队尾插，所以队首是老的)
                while (!dp.empty() && dp.front().index <= index - k) {
                    dp.pop_front();
                }
                //! 从队尾开始清除小的（因为在有新的大的情况下，之前的小的一点用没有）
                while (!dp.empty() && dp.back().v < val) {
                    dp.pop_back();
                }

                dp.push_back({val, index});
            }
        };

        MyDp mydp(k);
        for (int i = 0; i < k; i++) {
            mydp.push(nums[i], i);
        }

        vector<int> ret;
        for (int i = k; i < nums.size(); i++) {
            ret.push_back(mydp.dp.front().v);
            mydp.push(nums[i], i);
        }
        ret.push_back(mydp.dp.front().v);
        return ret;
    }
};
// @lc code=end
