/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */
#include "common.h"
// @lc code=start
class MinStack {
   public:
    MinStack() {}

    void push(int val) {
        elems.push_back(val);
        if (mins.empty()) {
            mins.push_back(val);
        } else if (mins.back() < val) {
            mins.push_back(mins.back());
        } else {
            mins.push_back(val);
        }
    }

    void pop() {
        elems.pop_back();
        mins.pop_back();
    }

    int top() { return elems.back(); }
    deque<int> elems;
    deque<int> mins;

    int getMin() { return mins.back(); }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end
