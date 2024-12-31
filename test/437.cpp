#include "437.路径总和-iii.cpp"

MYTEST(1) {
    Solution s;

    auto k = buildTree({0, 1, 1});
    s.pathSum(k, 0);
}
