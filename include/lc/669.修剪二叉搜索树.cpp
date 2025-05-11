/*
 * @lc app=leetcode.cn id=669 lang=cpp
 *
 * [669] 修剪二叉搜索树
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
    TreeNode* trimBST(TreeNode* p, int low, int high) {
        if (p == nullptr) {
            return nullptr;
        }

        if (p->val < low) {
            return trimBST(p->right, low, high);
        }

        if (p->val > high) {
            return trimBST(p->left, low, high);
        }
        TreeNode* new_left = trimBST(p->left, low, high);
        p->left = new_left;
        TreeNode* new_right = trimBST(p->right, low, high);
        p->right = new_right;
        return p;
    }
};
// @lc code=end
