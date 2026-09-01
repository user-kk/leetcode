/*
 * @lc app=leetcode.cn id=138 lang=cpp
 *
 * [138] 随机链表的复制
 */
#include "common.h"

namespace {
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

    //! 另一种O(1)空间的方法：可以把原本的没用的next当做一个map，指向新节点
    //! A -> A' -> B -> B' -> C -> C'
    Node* copyRandomList2(Node* head) {
        if (!head) {
            return nullptr;
        }

        // 1. A -> A' -> B -> B' ...
        for (Node* p = head; p != nullptr;) {
            Node* copy = new Node(p->val);
            copy->next = p->next;
            p->next = copy;

            p = copy->next;
        }

        // 2. 设置 random
        for (Node* p = head; p != nullptr; p = p->next->next) {
            if (p->random != nullptr) {
                p->next->random = p->random->next;
            }
        }

        // 3. 拆开两条链
        Node new_head{-1};
        Node* h = &new_head;

        for (Node* p = head; p != nullptr; p = p->next) {
            Node* copy = p->next;
            p->next = copy->next;

            h->next = copy;
            copy->next = nullptr;
            h = copy;
        }

        return new_head.next;
    }
};
// @lc code=end
}  // namespace