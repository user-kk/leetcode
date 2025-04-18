#include "common.h"
#include "debug_macro.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>  // 容器支持
#include <cpptrace/cpptrace.hpp>
#include <ostream>
#include <thread>

void postOrderTraversal(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* p = root;
    TreeNode* last = nullptr;
    while (p != nullptr) {
        s.push(p);
        last = p;
        p = p->left;
    }
    last = p;  // 出来时相当于遍历了空节点，所以赋值last

    while (!s.empty()) {
        // 检查栈顶右树是否为之前遍历的节点，如果是，输出，弹栈
        if (s.top()->right == last) {
            last = s.top();
            std::cout << s.top()->val << ' ';
            s.pop();
            continue;
        }

        p = s.top()->right;

        while (p != nullptr) {
            s.push(p);
            last = p;
            p = p->left;
        }
        last = p;  // 出来时相当于遍历了空节点，所以赋值last
    }
    std::cout << std::endl;
}

void midOrderTraversal(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* p = root;
    while (p != nullptr) {
        s.push(p);
        p = p->left;
    }

    while (!s.empty()) {
        std::cout << s.top()->val << ' ';

        p = s.top()->right;
        s.pop();

        while (p != nullptr) {
            s.push(p);
            p = p->left;
        }
    }
    std::cout << std::endl;
}

TEST(test1, test1_1) {
    auto root = buildTree({3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4});
    postOrderTraversal(root);
}

TEST(test1, test1_2) {
    auto root = buildList({4, 2, 1, 3});
    int a = 1;
}

TEST(test1, test1_3) {  // 使用后缀'vec'创建vector<int>对象
    std::vector<int> v = "[1,2,3,4]"_vec;
    std::vector<std::vector<int>> v2 = "[[1,2],[3,4]]"_vec2;
}

void kk(int a) { cpptrace::generate_trace().print(std::cout); }

TEST(test1, test1_4) {  // 使用后缀'vec'创建vector<int>对象
    kk(1);
    // 示例 JSON 数组
    std::string jsonString = "[[1,2],[3,4]]";

    auto vec = build2dVector(jsonString);

    fmt::println("{}", vec);
}

TEST(test1, test1_5) {
    int a1 = 10;
    double a2 = 20.5;
    std::string a3 = "Hello";
    // MYDEBUG(__FUNCTION__, std::this_thread::get_id(), a1, a2, a3);
    debug_macro(a1, a2, a3);
    debug_macro(a1, a2, a3);
}