/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode node(0);
        ListNode* p = &node;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                p->next = list1;
                p = p->next;
                list1 = list1->next;
            } else {
                p->next = list2;
                p = p->next;
                list2 = list2->next;
            }
        }
        while (list1 != nullptr) {
            p->next = list1;
            p = p->next;
            list1 = list1->next;
        }
        while (list2 != nullptr) {
            p->next = list2;
            p = p->next;
            list2 = list2->next;
        }
        p->next = nullptr;
        return node.next;
    }
};
// @lc code=end
