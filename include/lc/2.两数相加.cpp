/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* p1 = l1;
        ListNode* p2 = l2;

        int k = 0;
        ListNode head;
        ListNode* h = &head;
        while (p1 != nullptr && p2 != nullptr) {
            h->next = new ListNode((p1->val + p2->val + k) % 10, nullptr);
            k = (p1->val + p2->val + k) / 10;
            h = h->next;
            p1 = p1->next;
            p2 = p2->next;
        }

        while (p1 != nullptr) {
            h->next = new ListNode((p1->val + k) % 10, nullptr);
            k = (p1->val + k) / 10;
            h = h->next;
            p1 = p1->next;
        }

        while (p2 != nullptr) {
            h->next = new ListNode((p2->val + k) % 10, nullptr);
            k = (p2->val + k) / 10;
            h = h->next;
            p2 = p2->next;
        }

        if (k != 0) {
            h->next = new ListNode(k, nullptr);
        }
        return head.next;
    }
};
// @lc code=end
