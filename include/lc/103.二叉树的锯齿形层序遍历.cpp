/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层序遍历
 */
#include "common.h"
#include <algorithm>
#include <ranges>
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        vector<vector<int>> ret;

        std::deque<TreeNode*> q;

        q.push_back(root);

        bool flag = true;

        while (!q.empty()) {
            int n = q.size();
            vector<int> v;
            for (int i = 0; i < n; i++) {
                if (flag) {
                    TreeNode* t = q.front();
                    v.push_back(t->val);
                    q.pop_front();
                    if (t->left != nullptr) {
                        q.push_back(t->left);
                    }
                    if (t->right != nullptr) {
                        q.push_back(t->right);
                    }

                } else {
                    TreeNode* t = q.back();
                    v.push_back(t->val);
                    q.pop_back();

                    if (t->right != nullptr) {
                        q.push_front(t->right);
                    }
                    if (t->left != nullptr) {
                        q.push_front(t->left);
                    }
                }
            }
            flag = !flag;
            ret.push_back(std::move(v));
        }

        return ret;
    }
};
// @lc code=end
