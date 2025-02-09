/*
 * @lc app=leetcode.cn id=297 lang=cpp
 *
 * [297] 二叉树的序列化与反序列化
 */
#include "common.h"
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
class Codec {
   public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        s.push_back(',');
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto& t = q.front();
            if (t == nullptr) {
                s.append(to_string(-1001));
                s.append(",");
                q.pop();
                continue;
            }
            s.append(to_string(t->val));
            s.append(",");
            q.push(t->left);
            q.push(t->right);
            q.pop();
        }
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string& data) {
        TreeNode** k = nullptr;
        string_view data_view{data};
        int i = 0;
        TreeNode* root = nullptr;
        queue<TreeNode**> q;
        q.push(&root);

        while (i != data.size() - 1 && !q.empty()) {
            int pos = data_view.find(',', i + 1);
            int val = std::stoi(data.substr(i + 1, pos - i - 1));

            if (val != -1001) {
                TreeNode* t = new TreeNode(val);
                *(q.front()) = t;
                q.push(&t->left);
                q.push(&t->right);
            } else {
                *(q.front()) = nullptr;
            }
            q.pop();

            i = pos;
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
// @lc code=end
