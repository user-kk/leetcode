/*
 * @lc app=leetcode.cn id=226 lang=cpp
 *
 * [226] 翻转二叉树
 */
#include "common.h"
namespace {
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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }

        TreeNode* left = nullptr;
        if (root->left != nullptr) {
            left = invertTree(root->left);
        }

        TreeNode* rigth = nullptr;
        if (root->right != nullptr) {
            rigth = invertTree(root->right);
        }
        root->left = rigth;
        root->right = left;
        return root;
    }
};
// @lc code=end
}  // namespace