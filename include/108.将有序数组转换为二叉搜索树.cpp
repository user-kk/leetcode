/*
 * @lc app=leetcode.cn id=108 lang=cpp
 *
 * [108] 将有序数组转换为二叉搜索树
 */
#include <common.h>
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
    TreeNode* build(vector<int>& nums, int begin, int end) {
        int len = end - begin;
        if (len == 0) {
            return nullptr;
        }
        if (len == 1) {
            return new TreeNode(nums[begin]);
        }

        TreeNode* ret = new TreeNode(nums[begin + len / 2]);
        ret->left = build(nums, begin, begin + len / 2);
        ret->right = build(nums, begin + len / 2 + 1, end);
        return ret;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, nums.size());
    }
};
// @lc code=end
