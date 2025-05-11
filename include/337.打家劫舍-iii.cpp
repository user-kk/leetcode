/*
 * @lc app=leetcode.cn id=337 lang=cpp
 *
 * [337] 打家劫舍 III
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
    struct T {
        int left;
        int val;
        int right;
    };
    //! 首先确认遍历顺序，不应该是从上往下遍历，因为祖先节点会被每一个孩子节点加和，导致被计算多次
    //! 所以先考虑计算孩子节点，故为后序遍历
    //! 然后注意打家劫舍的dp的值并非为以某一点为终点的最优值，而是一个范围内的最优值
    //! 换句话说，打家劫舍的dp[i],i的那个点并不一定选中，可以为不选中
    //! 所以dp[i] = max(dp[下一层所有的值],dp[当前值+下下层所有的值])

    T robInternal(TreeNode* p) {
        if (p == nullptr) {
            return {0, 0, 0};
        }

        T left = robInternal(p->left);
        T right = robInternal(p->right);

        int val =
            std::max(p->val + left.left + left.right + right.left + right.right,
                     left.val + right.val);
        return {left.val, val, right.val};
    }

    int rob(TreeNode* root) {
        T t = robInternal(root);
        return t.val;
    }
};
// @lc code=end
