/*
 * @lc app=leetcode.cn id=102 lang=cpp
 *
 * [102] 二叉树的层序遍历
 */
#include <common.h>

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        queue<TreeNode*> q1;
        queue<TreeNode*> q2;

        q1.push(root);
        vector<vector<int>> ret;
        while (!q1.empty() || !q2.empty()) {
            vector<int> layor;
            while (!q1.empty()) {
                auto& t = q1.front();
                layor.push_back(t->val);
                if (t->left != nullptr) {
                    q2.push(t->left);
                }
                if (t->right != nullptr) {
                    q2.push(t->right);
                }
                q1.pop();
            }
            if (!layor.empty()) {
                ret.push_back(std::move(layor));
            }

            while (!q2.empty()) {
                auto& t = q2.front();
                layor.push_back(t->val);
                if (t->left != nullptr) {
                    q1.push(t->left);
                }
                if (t->right != nullptr) {
                    q1.push(t->right);
                }
                q2.pop();
            }
            if (!layor.empty()) {
                ret.push_back(std::move(layor));
            }
        }
        return ret;
    }
};
// @lc code=end
