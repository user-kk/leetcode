/*
 * @lc app=leetcode.cn id=234 lang=cpp
 *
 * [234] 回文链表
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
    bool isPalindrome(ListNode* head) {
        if (head->next == nullptr) {
            return true;
        }

        ListNode* s = head;
        ListNode* f = head;

        //! 二分链表的方法，快慢指针，其中slow的next不论奇偶数，
        //! 都是指向右侧二分后链表的起点
        while (f->next && f->next->next) {
            s = s->next;
            f = f->next->next;
        }
        s = s->next;

        ListNode p2_head(-1, nullptr);

        // 头插法倒排
        for (ListNode* p = s; p != nullptr;) {
            ListNode* t = p->next;
            p->next = p2_head.next;
            p2_head.next = p;
            p = t;
        }

        ListNode* p1 = head;
        ListNode* p2 = p2_head.next;

        while (p2 != nullptr) {
            if (p2->val != p1->val) {
                return false;
            }

            p1 = p1->next;
            p2 = p2->next;
        }

        return true;
    }
};
// @lc code=end
