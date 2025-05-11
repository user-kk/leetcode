/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
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
    //! find用hash表加速一下更好
    TreeNode* buildTreeInternal(vector<int>& preorder, int pre_l, int pre_r,
                                vector<int>& inorder, int in_l, int in_r) {
        if (pre_l == pre_r) {
            return nullptr;
        }
        auto* ret = new TreeNode(preorder[pre_l]);
        auto it = std::find(inorder.begin() + in_l, inorder.begin() + in_r,
                            preorder[pre_l]);
        int left_len = it - (inorder.begin() + in_l);
        ret->left = buildTreeInternal(preorder, pre_l + 1, pre_l + left_len + 1,
                                      inorder, in_l, in_l + left_len);
        ret->right = buildTreeInternal(preorder, pre_l + left_len + 1, pre_r,
                                       inorder, in_l + left_len + 1, in_r);
        return ret;
    }

   public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTreeInternal(preorder, 0, preorder.size(), inorder, 0,
                                 inorder.size());
    }
};
// @lc code=end
