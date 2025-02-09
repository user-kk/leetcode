/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层序遍历
 */
#include <common.h>
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

        std::deque<TreeNode*> q1, q2;

        q1.push_back(root);
        vector<int> layor;
        while (!q1.empty() || !q2.empty()) {
            for (auto* it : q1) {
                layor.push_back(it->val);
            }
            ret.push_back(std::move(layor));

            while (!q1.empty()) {
                if (q1.front()->left != nullptr) {
                    q2.push_back(q1.front()->left);
                }
                if (q1.front()->right != nullptr) {
                    q2.push_back(q1.front()->right);
                }

                q1.pop_front();
            }
            if (q2.empty()) {
                break;
            }
            for (auto it = q2.rbegin(); it != q2.rend(); it++) {
                layor.push_back((*it)->val);
            }
            ret.push_back(std::move(layor));

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
