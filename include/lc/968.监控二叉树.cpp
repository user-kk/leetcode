/*
 * @lc app=leetcode.cn id=968 lang=cpp
 *
 * [968] 监控二叉树
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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
   private:
    int ret = 0;
    enum T { IS_NULL, NEED_COVER, HAS_CAMERA, CAN_COVER };
    //! 贪心：从叶子节点往上找，叶子节点不放，然后每隔两个都必须放
    T minCameraCoverInternal(TreeNode* p) {
        if (p == nullptr) {
            return IS_NULL;
        }

        T left = minCameraCoverInternal(p->left);
        T right = minCameraCoverInternal(p->right);

        if (left == IS_NULL && right == IS_NULL) {
            return NEED_COVER;
        }

        if (left == NEED_COVER || right == NEED_COVER) {
            ret++;
            return HAS_CAMERA;
        }

        if (left == HAS_CAMERA || right == HAS_CAMERA) {
            return CAN_COVER;
        }
        // 到了这里是can_cover和is_null的组合,且不是全为is_null
        return NEED_COVER;
    }

   public:
    int minCameraCover(TreeNode* root) {
        if (minCameraCoverInternal(root) == NEED_COVER) {
            ret++;
        };
        return ret;
    }
};

// @lc code=end
}  // namespace
