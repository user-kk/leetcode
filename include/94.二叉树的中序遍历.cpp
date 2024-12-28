/*
 * @lc app=leetcode.cn id=94 lang=cpp
 *
 * [94] 二叉树的中序遍历
 */
#include <common.h>
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
    void traversal(TreeNode* p, vector<int>& ret) {
        if (p == nullptr) {
            return;
        }
        traversal(p->left, ret);
        ret.push_back(p->val);
        traversal(p->right, ret);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        traversal(root, ret);
        return ret;
    }
};
// @lc code=end
