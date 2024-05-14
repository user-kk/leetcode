/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
 */
#include <common.h>
namespace {

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 让ab链表相连(a的终点为b的起点,a的起点为b的终点)
// 长链b,短链a
// 当b走到b的终点(即a的起点)时
// a在b链上走了b-a米,距共同终点b-(b-a)=a米,同时b距终点也为a米
class Solution {
   public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1 = headA;
        ListNode *p2 = headB;
        while (p1 != p2) {
            p1 = (p1 == nullptr) ? headB : p1->next;
            p2 = (p2 == nullptr) ? headA : p2->next;
        }
        return p1;
    }
};
// @lc code=end
}  // namespace