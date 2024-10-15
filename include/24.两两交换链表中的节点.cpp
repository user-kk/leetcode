/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
 */
#include <common.h>
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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode new_head;
        new_head.next = head;
        ListNode* pre = &new_head;
        ListNode* p1 = head;
        ListNode* p2 = head->next;

        while (p1 != nullptr && p2 != nullptr) {
            p1->next = p2->next;
            p2->next = p1;
            pre->next = p2;
            pre = p1;
            p2 = p1->next == nullptr ? nullptr : p1->next->next;
            p1 = p1->next;
        }
        return new_head.next;
    }
};
// @lc code=end
