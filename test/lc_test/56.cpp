#include <vector>

#include "56.合并区间.cpp"

MYTEST(1) {
    Solution s;

    auto k = std::vector<std::vector<int>>{{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    s.merge(k);
}
