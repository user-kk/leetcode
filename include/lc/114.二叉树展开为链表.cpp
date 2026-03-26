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
    void flatten2(TreeNode* root) {
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

    //! 分治法： 把以root为根的子树展开为链表后，返回链表的尾部节点
    TreeNode* do_flatten(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* l_tail = do_flatten(root->left);
        TreeNode* r_tail = do_flatten(root->right);

        if (l_tail == nullptr && r_tail == nullptr) {
            return root;
        }

        if (l_tail != nullptr && r_tail != nullptr) {
            l_tail->right = root->right;
            l_tail->left = nullptr;
            root->right = root->left;
            root->left = nullptr;
            return r_tail;
        }

        if (l_tail == nullptr) {
            return r_tail;
        }

        if (r_tail == nullptr) {
            l_tail->right = root->right;
            l_tail->left = nullptr;
            root->right = root->left;
            root->left = nullptr;
            return l_tail;
        }

        return nullptr;
    }

    void flatten3(TreeNode* root) { do_flatten(root); }

    void flatten(TreeNode* root) {
        TreeNode* p = root;
        while (p != nullptr) {
            if (p->left == nullptr) {
                p = p->right;
                continue;
            }

            //! 有左子树，砍掉，先找左子树的最右节点为k
            TreeNode* k = p->left;
            while (k->right != nullptr) {
                k = k->right;
            }
            // 砍掉
            k->right = p->right;
            p->right = p->left;
            p->left = nullptr;

            p = p->right;
        }
    }
};
// @lc code=end
