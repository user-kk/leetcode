/*
 * @lc app=leetcode.cn id=538 lang=cpp
 *
 * [538] 把二叉搜索树转换为累加树
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
    TreeNode* convertBST(TreeNode* root) {
        TreeNode* p = root;
        int sum = 0;
        std::stack<TreeNode*> st;

        while (p != nullptr || !st.empty()) {
            while (p) {
                sum += p->val;
                st.push(p);
                p = p->left;
            }
            p = st.top()->right;
            st.pop();
        }

        int cur = 0;
        p = root;
        while (p != nullptr || !st.empty()) {
            while (p) {
                st.push(p);
                p = p->left;
            }
            int t = cur;
            cur += st.top()->val;
            st.top()->val = sum - t;
            p = st.top()->right;
            st.pop();
        }
        return root;
    }
};
// @lc code=end
