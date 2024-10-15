#include "54.螺旋矩阵.cpp"

MYTEST(1) {
    Solution s;
    auto a = std::vector<std::vector<int>>{
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    s.spiralOrder(a);
}
