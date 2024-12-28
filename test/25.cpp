#include "25.k-个一组翻转链表.cpp"

MYTEST(1) {
    Solution s;
    auto p = buildList({1, 2, 3, 4, 5});
    s.reverseKGroup(p, 2);
}
