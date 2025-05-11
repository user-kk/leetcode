/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
 */
#include "common.h"

#include <cstddef>
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
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* p = root;
        bool flag = true;
        int current = 0;

        st.push(root);
        while (!st.empty()) {
            while (p != nullptr && p->left != nullptr) {
                st.push(p->left);
                p = p->left;
            }

            p = st.top();
            st.pop();
            if (flag) {
                current = p->val;
                flag = false;
            } else {
                if (p->val <= current) {
                    return false;
                }
                current = p->val;
            }
            if (p->right != nullptr) {
                st.push(p->right);
                p = p->right;
            } else {
                p = nullptr;  // 向右走不了一定要注意弹栈再向右走
            }
        }
        return true;
    }
};
// @lc code=end
