#include "167.两数之和-ii-输入有序数组.cpp"

MYTEST(1) {
    Solution s;
    std::vector<int> a{1, 1};
    std::vector<int> b{1, 1 + 1};
    ASSERT_EQ(s.twoSum(a, 2), b);
}