/*
 * @lc app=leetcode.cn id=145 lang=cpp
 *
 * [145] 二叉树的后序遍历
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        TreeNode* p = root;
        TreeNode* last = nullptr;
        while (p != nullptr) {
            s.push(p);
            p = p->left;
        }
        last = p;  // 出来时相当于遍历了空节点，所以赋值last为空

        while (!s.empty()) {
            // 检查栈顶右树是否为之前遍历的节点，如果是，输出，弹栈
            if (s.top()->right == last) {
                last = s.top();  // 重要，不要忘了
                ret.push_back(s.top()->val);
                s.pop();
                continue;
            }

            p = s.top()->right;

            while (p != nullptr) {
                s.push(p);
                p = p->left;
            }
            last = p;  // 出来时相当于遍历了空节点，所以赋值last为空
        }
        return ret;
    }
};
// @lc code=end
