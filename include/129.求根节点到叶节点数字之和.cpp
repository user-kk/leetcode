/*
 * @lc app=leetcode.cn id=129 lang=cpp
 *
 * [129] 求根节点到叶节点数字之和
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
    int ret = 0;
    void traversal(TreeNode* p, int val) {
        if (p->left == nullptr && p->right == nullptr) {
            ret += (val * 10 + p->val);
            return;
        }

        if (p->left != nullptr) {
            traversal(p->left, val * 10 + p->val);
        }

        if (p->right != nullptr) {
            traversal(p->right, val * 10 + p->val);
        }
    }
    int sumNumbers(TreeNode* root) {
        traversal(root, 0);
        return ret;
    }
};
// @lc code=end
