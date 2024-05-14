#include "1.两数之和.cpp"

MYTEST(1) {
    Solution s;
    std::vector<int> a{1, 1};
    std::vector<int> b{0, 1};
    ASSERT_EQ(s.twoSum(a, 2), b);
    ASSERT_TRUE(true) << testing::PrintToString(a);
}

MYTEST(2) {
    Solution s;
    std::vector<int> a{2, 3, 4, 5};
    std::vector<int> b{2, 3};
    ASSERT_EQ(s.twoSum(a, 9), b);
}