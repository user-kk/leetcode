/*
 * @lc app=leetcode.cn id=257 lang=cpp
 *
 * [257] 二叉树的所有路径
 */
#include "common.h"

#include <string>
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
    vector<string> ret;
    deque<int> path;
    void find(TreeNode* t) {
        if (t == nullptr) {
            return;
        }
        path.push_back(t->val);

        find(t->left);
        find(t->right);

        if (t->left == nullptr && t->right == nullptr) {
            string s;
            for (int i : path) {
                s.append(std::to_string(i) + "->");
            }
            s.pop_back();
            s.pop_back();
            ret.push_back(std::move(s));
        }
        path.pop_back();
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        find(root);
        return std::move(ret);
    }
};
// @lc code=end
