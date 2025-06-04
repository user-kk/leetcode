/*
 * @lc app=leetcode.cn id=328 lang=cpp
 *
 * [328] 奇偶链表
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
    ListNode* oddEvenList(ListNode* head) {
        ListNode odd;
        ListNode even;
        ListNode* odd_tail_node = &odd;
        ListNode* even_tail_node = &even;
        bool is_odd = true;
        for (ListNode* p = head; p != nullptr; p = p->next) {
            if (is_odd) {
                odd_tail_node->next = p;
                odd_tail_node = p;
                is_odd = false;
            } else {
                even_tail_node->next = p;
                even_tail_node = p;
                is_odd = true;
            }
        }
        odd_tail_node->next = even.next;
        even_tail_node->next = nullptr;
        return odd.next;
    }
};
// @lc code=end
