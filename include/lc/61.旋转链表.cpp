/*
 * @lc app=leetcode.cn id=61 lang=cpp
 *
 * [61] 旋转链表
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
    //! 链表的旋转先成环再切
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) {
            return nullptr;
        }

        int len = 1;
        ListNode* p = head;

        while (p->next != nullptr) {
            len++;
            p = p->next;
        }

        p->next = head;
        k = k % len;

        ListNode* p2 = head;

        // 移动i-1次后断环
        for (int i = len - k; i > 1; i--) {
            p2 = p2->next;
        }

        ListNode* ret = p2->next;
        p2->next = nullptr;
        return ret;
    }
};
// @lc code=end
