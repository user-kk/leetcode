/*
 * @lc app=leetcode.cn id=235 lang=cpp
 *
 * [235] 二叉搜索树的最近公共祖先
 */
#include "common.h"
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//! 找第一个分歧点
class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* k = root;

        while (k) {
            if (k->val < p->val && k->val < q->val) {
                k = k->right;
            } else if (k->val > p->val && k->val > q->val) {
                k = k->left;
            } else {
                return k;
            }
        }
        return nullptr;
    }
};
// @lc code=end
