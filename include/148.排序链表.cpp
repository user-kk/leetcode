/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] 排序链表
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
    ListNode* part(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* last = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            last = slow;
            slow = slow->next;
        }
        last->next = nullptr;
        return slow;
    }
    ListNode* merge(ListNode* leftHead, ListNode* rightHead) {
        ListNode node(-1);
        ListNode* p = &node;
        while (leftHead != nullptr && rightHead != nullptr) {
            if (leftHead->val < rightHead->val) {
                p->next = leftHead;
                p = p->next;
                leftHead = leftHead->next;
            } else {
                p->next = rightHead;
                p = p->next;
                rightHead = rightHead->next;
            }
        }

        if (leftHead != nullptr) {
            p->next = leftHead;
        } else {
            p->next = rightHead;
        }

        return node.next;
    }

    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* midNode = part(head);
        ListNode* leftHead = sortList(head);
        ListNode* rightHead = sortList(midNode);
        return merge(leftHead, rightHead);
    }
};
// @lc code=end
