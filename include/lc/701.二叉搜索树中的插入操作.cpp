/*
 * @lc app=leetcode.cn id=701 lang=cpp
 *
 * [701] 二叉搜索树中的插入操作
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }
        TreeNode* p = root;
        TreeNode* pre = nullptr;
        while (p) {
            if (val < p->val) {
                pre = p;
                p = p->left;
            } else {
                pre = p;
                p = p->right;
            }
        }
        if (val < pre->val) {
            pre->left = new TreeNode(val);
        } else {
            pre->right = new TreeNode(val);
        }
        return root;
    }
};
// @lc code=end
