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
    //! 另一种O(1)空间的方法：可以把原本的没用的next当做一个map，指向新节点
    //! 新节点先直接复制，然后随机节点的新值=(*(新节点的随机节点))->next
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
}  // namespace