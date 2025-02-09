/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 */
#include "common.h"
namespace {
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// class Solution {
//    public:
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
//     {
//         struct E {
//             TreeNode* k;
//             size_t p;
//         };
//         struct E2 {
//             TreeNode* k;
//             size_t me;
//         };
//         std::vector<E> v;
//         size_t p_i;
//         size_t q_i;
//         v.push_back({root, 0});

//         std::queue<E2> qu;
//         qu.push({root, 0});
//         while (!qu.empty()) {
//             size_t parent = qu.front().me;
//             if (qu.front().k == p) {
//                 p_i = parent;
//             } else if (qu.front().k == q) {
//                 q_i = parent;
//             }
//             if (qu.front().k->left != nullptr) {
//                 qu.push({qu.front().k->left, v.size()});
//                 v.push_back({qu.front().k->left, parent});
//             }
//             if (qu.front().k->right != nullptr) {
//                 qu.push({qu.front().k->right, v.size()});
//                 v.push_back({qu.front().k->right, parent});
//             }
//             qu.pop();
//         }
//         while (p_i != q_i) {
//             if (p_i < q_i) {
//                 q_i = v[q_i].p;
//             } else if (p_i > q_i) {
//                 p_i = v[p_i].p;
//             }
//         }
//         return v[p_i].k;
//     }
// };
class Solution {
   public:
    TreeNode* ans;
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return false;
        bool lson = dfs(root->left, p, q);
        bool rson = dfs(root->right, p, q);
        // 左右有 或 自己有时左右二者中有一个
        if ((lson && rson) ||
            ((root->val == p->val || root->val == q->val) && (lson || rson))) {
            ans = root;
        }

        // 左有或右有或自己有
        return lson || rson || root->val == p->val || root->val == q->val;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);
        return ans;
    }
};
// @lc code=end
}  // namespace