/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
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
    int ret = INT_MIN;
    int traversal(TreeNode* p) {
        if (p == nullptr) {
            return 0;
        }
        int left = traversal(p->left);
        int right = traversal(p->right);
        int val = std::max({left, right});
        if (left + right > ret) {
            ret = left + right;
        }
        return val + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        traversal(root);
        return ret;
    }
};
// @lc code=end
