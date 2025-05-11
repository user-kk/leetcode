#include "124.二叉树中的最大路径和.cpp"

MYTEST(1) {
    Solution s;
    auto p = buildTree({5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1});
    s.maxPathSum(p);
}
