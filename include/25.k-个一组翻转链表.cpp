/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode ret(0);
        ListNode* new_head = &ret;
        ListNode* next_head = new_head;
        ListNode* p = head;
        while (true) {
            next_head = p;
            for (int i = 0; i < k; i++) {
                // 到了最后一节，重新翻转一下，因为题中要求最后一节顺序不变
                if (p == nullptr) {
                    p = new_head->next;
                    new_head->next = nullptr;
                    while (p != nullptr) {
                        ListNode* t = p->next;
                        p->next = new_head->next;
                        new_head->next = p;
                        p = t;
                    }
                    return ret.next;
                }
                ListNode* t = p->next;
                p->next = new_head->next;
                new_head->next = p;
                p = t;
            }
            new_head = next_head;
        }
    }
};
// @lc code=end
