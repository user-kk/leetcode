/*
 * @lc app=leetcode.cn id=427 lang=cpp
 *
 * [427] 建立四叉树
 */

#include "common.h"
namespace {

class Node {
   public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
         Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

// @lc code=start
// Definition for a QuadTree node.

class Solution {
   private:
    Node* construct(vector<vector<int>>& grid, int x, int y, int len) {
        if (len == 1) {
            return new Node{static_cast<bool>(grid[x][y]), true};
        }
        int new_len = len / 2;
        Node* top_left_node = construct(grid, x, y, new_len);
        Node* top_right_node = construct(grid, x, y + new_len, new_len);
        Node* bottom_left_node = construct(grid, x + new_len, y, new_len);
        Node* bottom_right_node =
            construct(grid, x + new_len, y + new_len, new_len);
        Node* new_node = new Node{true,
                                  false,
                                  top_left_node,
                                  top_right_node,
                                  bottom_left_node,
                                  bottom_right_node};
        if (top_left_node->isLeaf && top_right_node->isLeaf &&
            bottom_left_node->isLeaf && bottom_right_node->isLeaf &&
            (top_left_node->val == top_right_node->val &&
             top_right_node->val == bottom_left_node->val &&
             bottom_left_node->val == bottom_right_node->val)) {
            new_node->val = top_left_node->val;
            new_node->isLeaf = true;
            new_node->topLeft = nullptr;
            new_node->topRight = nullptr;
            new_node->bottomLeft = nullptr;
            new_node->bottomRight = nullptr;
        }
        return new_node;
    }

   public:
    Node* construct(vector<vector<int>>& grid) {
        return construct(grid, 0, 0, grid.size());
    }
};
// @lc code=end
}  // namespace
