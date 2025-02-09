/*
 * @lc app=leetcode.cn id=114 lang=cpp
 *
 * [114] 二叉树展开为链表
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
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        TreeNode* p = root;
        TreeNode* pre = nullptr;
        std::stack<TreeNode*> st;

        while (p != nullptr || !st.empty()) {
            while (p != nullptr) {
                st.push(p);
                if (pre != nullptr) [[likely]] {
                    pre->left = p;
                }
                pre = p;
                p = p->left;
            }
            p = st.top();
            st.pop();
            p = p->right;
        }

        p = root;
        while (p != nullptr) {
            std::swap(p->left, p->right);
            p->left = nullptr;
            p = p->right;
        }
    }
};
// @lc code=end
