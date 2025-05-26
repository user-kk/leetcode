/*
 * @lc app=leetcode.cn id=295 lang=cpp
 *
 * [295] 数据流的中位数
 */
#include <functional>
#include <queue>
#include "common.h"
// @lc code=start
class MedianFinder {
   public:
    MedianFinder() {}

    void addNum(int num) {
        if (left.empty() || num <= left.top()) {
            left.push(num);
            if (left.size() > right.size() + 1) {
                // 左边的多了，平衡一下
                right.push(left.top());
                left.pop();
            }
        } else {
            right.push(num);
            if (right.size() > left.size()) {
                // 右边的多了，平衡一下
                left.push(right.top());
                right.pop();
            }
        }
    }

    double findMedian() {
        if (left.size() > right.size()) {
            // 说明是奇数
            return left.top();
        } else {
            // 说明是偶数
            return (left.top() + right.top()) / 2.0;
        }
    }

   private:
    priority_queue<int> left;  // 小的那一半
    priority_queue<int, std::vector<int>, std::greater<int>> right;  // 大的
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
// @lc code=end
