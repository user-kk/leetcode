/*
 * @lc app=leetcode.cn id=124 lang=cpp
 *
 * [124] 二叉树中的最大路径和
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
    // 找到包含这个节点的最大的路径
    // 但是为了使上层形成路径，返回的值不能是right + left + p->val
    int traversal(TreeNode* p) {
        if (p == nullptr) {
            return 0;
        }
        int left = traversal(p->left);
        int right = traversal(p->right);
        int val = std::max(
            {p->val, left + p->val, right + p->val, right + left + p->val});
        if (val > ret) {
            ret = val;  // 保存的时候可以包含自己的节点
        }
        return std::max({p->val, left + p->val, right + p->val});
    }
    int maxPathSum(TreeNode* root) {
        traversal(root);
        return ret;
    }
};
// @lc code=end
