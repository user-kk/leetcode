/*
 * @lc app=leetcode.cn id=138 lang=cpp
 *
 * [138] 随机链表的复制
 */
#include "common.h"

#include <unordered_map>
class Node {
   public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
   public:
    Node* copyRandomList(Node* head) {
        Node* p1 = head;
        Node new_head{0};
        Node* p2 = &new_head;
        std::unordered_map<Node*, Node*> m;
        m.insert({nullptr, nullptr});

        while (p1 != nullptr) {
            p2->next = new Node(p1->val);
            m.insert({p1, p2->next});
            p1 = p1->next;
            p2 = p2->next;
        }
        p2->next = nullptr;

        p1 = head;
        p2 = new_head.next;
        while (p1 != nullptr) {
            p2->random = m[p1->random];
            p1 = p1->next;
            p2 = p2->next;
        }
        return new_head.next;
    }
};
// @lc code=end
