/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
 */
#include "common.h"

#include <cstddef>
#include <optional>
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
        std::optional<int> current = std::nullopt;
        //! 非递归遍历树
        while (p != nullptr || !st.empty()) {
            while (p != nullptr) {
                st.push(p);
                p = p->left;
            }
            TreeNode* t = st.top();
            st.pop();
            if (!current.has_value()) {
                current = t->val;
            } else [[likely]] {
                if (t->val <= current.value()) {
                    return false;
                }

                current = t->val;
            }

            p = t->right;
        }
        return true;
    }
};
// @lc code=end
