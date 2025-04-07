#include "18.四数之和.cpp"

MYTEST(1) {
    auto v = "[2,2,2,2,2]"_vec;
    Solution s;
    s.fourSum(v, 8);
}

MYTEST(2) {
    auto v = "[1000000000,1000000000,1000000000,1000000000]"_vec;
    Solution s;
    s.fourSum(v, 8);
}
