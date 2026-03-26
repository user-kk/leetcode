/*
 * @lc app=leetcode.cn id=101 lang=cpp
 *
 * [101] 对称二叉树
 */
#include "common.h"
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

class Solution {
   public:
    bool isSymmetric2(TreeNode* root) {
        std::deque<TreeNode*> q1;
        std::deque<TreeNode*> q2;
        q1.push_back(root);
        auto cmp = [](TreeNode* a, TreeNode* b) {
            if (a != nullptr && b != nullptr && a->val == b->val) {
                return true;
            } else if (a == nullptr && b == nullptr) {
                return true;
            } else {
                return false;
            }
        };
        while (!q1.empty() || !q2.empty()) {
            if (!equal(q1.begin(), q1.end(), q1.rbegin(), q1.rend(), cmp)) {
                return false;
            }
            while (!q1.empty()) {
                if (q1.front() == nullptr) {
                    q1.pop_front();
                    continue;
                }
                q2.push_back(q1.front()->left);
                q2.push_back(q1.front()->right);
                q1.pop_front();
            }
            if (!equal(q2.begin(), q2.end(), q2.rbegin(), q2.rend(), cmp)) {
                return false;
            }
            while (!q2.empty()) {
                if (q2.front() == nullptr) {
                    q2.pop_front();
                    continue;
                }
                q1.push_back(q2.front()->left);
                q1.push_back(q2.front()->right);
                q2.pop_front();
            }
        }
        return true;
    }

    //! 检查a，b两颗子树是否轴对称（a的左和b的右轴对称并且a的右和b的左轴对称）
    bool check(TreeNode* l, TreeNode* r) {
        if (l == nullptr && r == nullptr) {
            return true;
        }

        if (l != nullptr && r != nullptr) {
            return (l->val == r->val) && check(l->left, r->right) &&
                   check(l->right, r->left);
        }
        return false;
    }

    bool isSymmetric(TreeNode* root) { return check(root->left, root->right); }
};
// @lc code=end
