/*
 * @lc app=leetcode.cn id=106 lang=cpp
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
   private:
    TreeNode* buildTreeInternal(vector<int>& postorder, int post_l, int post_r,
                                vector<int>& inorder, int in_l, int in_r) {
        if (post_l == post_r) {
            return nullptr;
        }
        auto* ret = new TreeNode(postorder[post_r - 1]);
        auto it = std::find(inorder.begin() + in_l, inorder.begin() + in_r,
                            postorder[post_r - 1]);
        int left_len = it - (inorder.begin() + in_l);
        ret->left = buildTreeInternal(postorder, post_l, post_l + left_len,
                                      inorder, in_l, in_l + left_len);
        ret->right = buildTreeInternal(postorder, post_l + left_len, post_r - 1,
                                       inorder, in_l + left_len + 1, in_r);
        return ret;
    }

   public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTreeInternal(postorder, 0, postorder.size(), inorder, 0,
                                 inorder.size());
    }
};
// @lc code=end
