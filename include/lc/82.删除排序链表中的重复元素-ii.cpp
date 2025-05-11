/*
 * @lc app=leetcode.cn id=82 lang=cpp
 *
 * [82] 删除排序链表中的重复元素 II
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode new_head(-101);
        ListNode* p2 = &new_head;
        ListNode* p2_pre = &new_head;
        int has_same = false;
        for (ListNode* p = head; p != nullptr; p = p->next) {
            if (p2->val != p->val) {
                if (has_same) {
                    p2 = p2_pre;
                    has_same = false;
                }
                p2_pre = p2;
                p2->next = p;
                p2 = p;
            } else {
                has_same = true;
            }
        }
        if (has_same) {
            p2 = p2_pre;
        }
        p2->next = nullptr;
        return new_head.next;
    }
};
// @lc code=end
