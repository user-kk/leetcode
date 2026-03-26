/*
 * @lc app=leetcode.cn id=437 lang=cpp
 *
 * [437] 路径总和 III
 */
#include "common.h"
#include <unordered_map>
#include <unordered_set>

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
        // 这是从根节点向下找的方法，开销较小，每层只需存储一个值
        if (p == nullptr) {
            return;
        }
        currentSum += p->val;
        countMap.insert(currentSum);
        pathSumInteral(countMap, p->left, targetSum, currentSum, ret);
        pathSumInteral(countMap, p->right, targetSum, currentSum, ret);
        //! extract是删除一个，而非具有相同值的全部，也可以用迭代器删，也是能保证删一个
        countMap.extract(currentSum);
        ret += countMap.count(currentSum - targetSum);
    }
    int pathSum2(TreeNode *root, int targetSum) {
        int ret = 0;
        std::unordered_multiset<long> countMap;
        countMap.insert(0);
        pathSumInteral(countMap, root, targetSum, 0, ret);
        return ret;
    }

    std::unordered_multiset<long> _pathSum(TreeNode *root, int targetSum,
                                           int &count) {
        // 这是从叶子节点向上找的方法，开销比较大
        if (root == nullptr) {
            return {};
        }
        auto left_set = _pathSum(root->left, targetSum, count);
        auto right_set = _pathSum(root->right, targetSum, count);
        if (targetSum == root->val) {
            count++;
        }
        count += left_set.count(targetSum - root->val);
        count += right_set.count(targetSum - root->val);

        std::unordered_multiset<long> ret;
        ret.insert(root->val);
        for (int i : left_set) {
            ret.insert(i + root->val);
        }
        for (int i : right_set) {
            ret.insert(i + root->val);
        }
        return ret;
    }

    int pathSum(TreeNode *root, int targetSum) {
        int ret = 0;
        _pathSum(root, targetSum, ret);
        return ret;
    }
};
// @lc code=end
