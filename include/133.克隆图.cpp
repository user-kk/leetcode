/*
 * @lc app=leetcode.cn id=133 lang=cpp
 *
 * [133] 克隆图
 */
#include <common.h>
// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
   public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        unordered_map<Node*, Node*> m;
        queue<Node*> q;  // 队列中的是已被new出来但是子节点还没更改的

        Node* new_root = new Node(node->val, node->neighbors);
        m.insert({node, new_root});
        q.push(new_root);

        while (!q.empty()) {
            Node* n = q.front();
            q.pop();
            auto& children = n->neighbors;
            for (int i = 0; i < children.size(); i++) {
                if (auto it = m.find(children[i]); it != m.end()) {
                    children[i] = it->second;
                } else {
                    Node* p =
                        new Node(children[i]->val, children[i]->neighbors);
                    m.insert({children[i], p});
                    children[i] = p;
                    q.push(p);
                }
            }
        }
        return new_root;
    }
};
// @lc code=end
