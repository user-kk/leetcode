/*
 * @lc app=leetcode.cn id=450 lang=cpp
 *
 * [450] 删除二叉搜索树中的节点
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
   private:
    void deleteNodeInternal(TreeNode*& p) {
        if (p->left == nullptr && p->right == nullptr) {
            p = nullptr;
            return;
        }

        if (p->left != nullptr && p->right == nullptr) {
            p = p->left;
            return;
        }

        if (p->left == nullptr && p->right != nullptr) {
            p = p->right;
            return;
        }

        TreeNode* l = p->left;
        TreeNode* r = p->right;
        p = p->right;
        TreeNode* k = r->left;
        r->left = l;
        while (l->right) {
            l = l->right;
        }
        l->right = k;
    }

   public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode** p = &root;
        while (*p) {
            if ((*p)->val < key) {
                p = &((*p)->right);
            } else if ((*p)->val > key) {
                p = &((*p)->left);
            } else {
                deleteNodeInternal(*p);
                return root;
            }
        }
        return root;
    }
};
// @lc code=end
