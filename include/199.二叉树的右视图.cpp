/*
 * @lc app=leetcode.cn id=199 lang=cpp
 *
 * [199] 二叉树的右视图
 */
#include <common.h>
#include <queue>
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
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        std::deque<TreeNode*> q1, q2;
        q1.push_back(root);
        vector<int> ret;
        while (!q1.empty() || !q2.empty()) {
            if (!q1.empty()) {
                ret.push_back(q1.back()->val);
            }
            while (!q1.empty()) {
                if (q1.front()->left != nullptr) {
                    q2.push_back(q1.front()->left);
                }
                if (q1.front()->right != nullptr) {
                    q2.push_back(q1.front()->right);
                }
                q1.pop_front();
            }
            if (!q2.empty()) {
                ret.push_back(q2.back()->val);
            }
            while (!q2.empty()) {
                if (q2.front()->left != nullptr) {
                    q1.push_back(q2.front()->left);
                }
                if (q2.front()->right != nullptr) {
                    q1.push_back(q2.front()->right);
                }
                q2.pop_front();
            }
        }
        return ret;
    }
};
// @lc code=end
