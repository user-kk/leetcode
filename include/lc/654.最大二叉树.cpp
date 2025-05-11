/*
 * @lc app=leetcode.cn id=654 lang=cpp
 *
 * [654] 最大二叉树
 */
#include <algorithm>
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
   private:
    TreeNode* constructMaximumBinaryTreeInternal(std::span<int> nums) {
        if (nums.empty()) {
            return nullptr;
        }

        auto it = std::max_element(nums.begin(), nums.end());
        TreeNode* left = constructMaximumBinaryTreeInternal({nums.begin(), it});
        TreeNode* right =
            constructMaximumBinaryTreeInternal({it + 1, nums.end()});
        return new TreeNode(*it, left, right);
    }

   public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return constructMaximumBinaryTreeInternal(nums);
    }
};
// @lc code=end
