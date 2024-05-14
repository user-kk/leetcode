#include <common.h>

TEST(test1, test1_1) {
    auto root = buildTree({3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4});
    ASSERT_NE(root, nullptr);
}

MYTEST(2) { std::cout << "Aaa" << std::endl; }

MYTEST(3) {
    std::cout << "Abb" << std::endl;
    int a = 1;
}
