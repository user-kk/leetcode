/*
 * @lc app=leetcode.cn id=117 lang=cpp
 *
 * [117] 填充每个节点的下一个右侧节点指针 II
 */
#include "common.h"
namespace {
class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

// using ::Node;
// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
   public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }
        deque<Node*> q1;
        deque<Node*> q2;
        q1.push_back(root);
        while (!q1.empty() || !q2.empty()) {
            for (int i = 1; i < q1.size(); i++) {
                q1[i - 1]->next = q1[i];
            }
            if (!q1.empty()) {
                q1.back()->next = nullptr;
            }

            while (!q1.empty()) {
                Node* t = q1.front();
                q1.pop_front();
                if (t->left != nullptr) {
                    q2.push_back(t->left);
                }
                if (t->right != nullptr) {
                    q2.push_back(t->right);
                }
            }

            for (int i = 1; i < q2.size(); i++) {
                q2[i - 1]->next = q2[i];
            }
            if (!q2.empty()) {
                q2.back()->next = nullptr;
            }

            while (!q2.empty()) {
                Node* t = q2.front();
                q2.pop_front();
                if (t->left != nullptr) {
                    q1.push_back(t->left);
                }
                if (t->right != nullptr) {
                    q1.push_back(t->right);
                }
            }
        }
        return root;
    }
};

// @lc code=end
}  // namespace
