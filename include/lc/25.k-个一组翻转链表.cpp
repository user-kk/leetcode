/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
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
    // last是第k+1个（哨兵）
    ListNode* reverseList(ListNode* pre, ListNode* p, ListNode* last) {
        ListNode* head = pre;

        //! 重要,与普通的翻转链表不同，普通的翻转链表头的next是nullptr
        //! 这个要单独设置
        head->next = last;

        ListNode* next_pre = p;
        while (p != last) {
            ListNode* k = p->next;
            p->next = head->next;
            head->next = p;
            p = k;
        }

        return next_pre;
    }

    ListNode* findKAndReverse(ListNode* head, int k) {
        int i = 0;
        ListNode* p = head->next;
        ListNode* last = nullptr;
        while (p != nullptr && i < k) {
            p = p->next;
            i++;
        }

        if (i < k) {
            return nullptr;
        }

        last = p;
        return reverseList(head, head->next, last);
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode new_head;
        new_head.next = head;

        ListNode* p = &new_head;

        p = findKAndReverse(p, k);

        while (p != nullptr) {
            p = findKAndReverse(p, k);
        }
        return new_head.next;
    }
};
// @lc code=end
