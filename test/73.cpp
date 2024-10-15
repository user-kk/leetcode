#include <vector>

#include "73.矩阵置零.cpp"

MYTEST(1) {
    Solution s;
    auto a =
        std::vector<std::vector<int>>{{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
    s.setZeroes(a);
}
