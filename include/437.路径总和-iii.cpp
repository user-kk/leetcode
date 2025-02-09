/*
 * @lc app=leetcode.cn id=437 lang=cpp
 *
 * [437] 路径总和 III
 */
#include "common.h"
#include <unordered_map>

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
    void pathSumInteral(std::unordered_multiset<long> &countMap, TreeNode *p,
                        int targetSum, long currentSum, int &ret) {
        if (p == nullptr) {
            return;
        }
        currentSum += p->val;
        countMap.insert(currentSum);
        pathSumInteral(countMap, p->left, targetSum, currentSum, ret);
        pathSumInteral(countMap, p->right, targetSum, currentSum, ret);
        countMap.extract(currentSum);
        ret += countMap.count(currentSum - targetSum);
    }
    int pathSum(TreeNode *root, int targetSum) {
        int ret = 0;
        std::unordered_multiset<long> countMap;
        countMap.insert(0);
        pathSumInteral(countMap, root, targetSum, 0, ret);
        return ret;
    }
};
// @lc code=end
