/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
// 利用快慢指针
class Solution {
   public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode node(-1, head);
        ListNode* slow = &node;
        ListNode* fast = &node;
        for (int i = 1; i <= n; i++) {
            fast = fast->next;
        }

        while (fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        ListNode* p = slow->next;
        slow->next = slow->next->next;
        delete p;
        return node.next;
    }
};
// @lc code=end
