/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
 */
#include "common.h"
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode node(0, head);
        ListNode* pre = &node;
        ListNode* p = pre;

        for (int i = 0; i < left - 1; i++) {
            p = p->next;
        }
        pre = p;
        p = p->next;
        ListNode* tail = p;
        for (int i = 0; i < right - left + 1; i++) {
            ListNode* t = p->next;
            p->next = pre->next;
            pre->next = p;
            p = t;
        }
        tail->next = p;
        return node.next;
    }
};
// @lc code=end
