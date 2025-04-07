/*
 * @lc app=leetcode.cn id=617 lang=cpp
 *
 * [617] 合并二叉树
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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 == nullptr) {
            return nullptr;
        }

        if (root1 == nullptr && root2 != nullptr) {
            TreeNode* left = mergeTrees(nullptr, root2->left);
            TreeNode* right = mergeTrees(nullptr, root2->right);
            return new TreeNode(root2->val, left, right);
        }
        if (root1 != nullptr && root2 == nullptr) {
            TreeNode* left = mergeTrees(root1->left, nullptr);
            TreeNode* right = mergeTrees(root1->right, nullptr);
            return new TreeNode(root1->val, left, right);
        }

        TreeNode* left = mergeTrees(root1->left, root2->left);
        TreeNode* right = mergeTrees(root1->right, root2->right);
        return new TreeNode(root1->val + root2->val, left, right);
    }
};
// @lc code=end
