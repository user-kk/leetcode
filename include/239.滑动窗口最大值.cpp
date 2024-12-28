/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    struct T {
        int val;
        int index;
    };
    // 单调队列
    class MyQueue {
       public:
        void push(T t) {
            if (dq.empty()) {
                dq.push_back(t);
                return;
            }

            if (t.val >= dq.back().val) {
                dq.clear();
                dq.push_back(t);
                return;
            }

            while (dq.front().val <= t.val) {
                dq.pop_front();
            }
            dq.push_front(t);
        }
        int back(int invalid_index) {
            while (dq.back().index <= invalid_index) {
                dq.pop_back();
            }
            return dq.back().val;
        }

       private:
        deque<T> dq;
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ret;
        MyQueue q;
        for (int i = 0; i < k; i++) {
            q.push(T{nums[i], i});
        }

        for (int i = 0; i + k < nums.size(); i++) {
            ret.push_back(q.back(i - 1));
            q.push(T{nums[i + k], i + k});
        }
        ret.push_back(q.back(static_cast<int>(nums.size()) - k - 1));
        return ret;
    }
};
// @lc code=end
