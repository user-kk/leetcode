/*
 * @lc app=leetcode.cn id=173 lang=cpp
 *
 * [173] 二叉搜索树迭代器
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
class BSTIterator {
   public:
    BSTIterator(TreeNode* root) {
        p = root;
        while (p) {
            st.push(p);
            p = p->left;
        }
        p = st.empty() ? nullptr : st.top();
    }

    int next() {
        int ret = p->val;
        st.pop();
        p = p->right;
        while (p) {
            st.push(p);
            p = p->left;
        }
        p = st.empty() ? nullptr : st.top();
        return ret;
    }

    bool hasNext() { return p != nullptr; }

    std::stack<TreeNode*> st;
    TreeNode* p = nullptr;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
// @lc code=end
