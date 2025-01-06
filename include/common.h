#include <gtest/gtest.h>

#include <algorithm>
#include <cstdio>
#include <initializer_list>
#include <numeric>
#include <queue>
#include <span>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define _CONCAT(a, b) a##b

#define CONCAT(a, b) _CONCAT(a, b)

#define MYTEST(num) TEST(CONCAT(_, CURRENT_FILE), CONCAT(_, num))

#define N_B namespace {
#define N_E }

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Node {
   public:
    int val;
    vector<Node *> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

inline TreeNode *buildTree(const std::vector<int> &list) {
    TreeNode *root = nullptr;
    std::queue<TreeNode **> q;
    q.push(&root);
    for (int i : list) {
        if (i == -1) {
            *(q.front()) = nullptr;
            q.pop();
            continue;
        }
        TreeNode *node = new TreeNode(i);
        *(q.front()) = node;
        q.push(&(node->left));
        q.push(&(node->right));
        q.pop();
    }
    return root;
}

inline ListNode *buildList(const std::vector<int> &list) {
    ListNode k(-1);
    ListNode *p = &k;
    for (int i : list) {
        p->next = new ListNode(i);
        p = p->next;
    }
    p->next = nullptr;
    return k.next;
}

template <typename T>
std::vector<T> createVector(std::initializer_list<T> il) {
    return std::vector<T>(il);
}

template <typename T>
std::vector<std::vector<T>> createVector(
    std::initializer_list<std::initializer_list<T>> il) {
    std::vector<std::vector<T>> vec;
    for (auto &sub_il : il) {
        vec.push_back(createVector(sub_il));
    }
    return vec;
}

template <typename T>
std::vector<std::vector<std::vector<T>>> createVector(
    std::initializer_list<std::initializer_list<std::initializer_list<T>>> il) {
    std::vector<std::vector<std::vector<T>>> vec;
    for (auto &sub_il : il) {
        vec.push_back(createVector(sub_il));
    }
    return vec;
}

inline std::vector<int> buildVector(std::istream &in) {
    vector<int> vec;
    int num = 0;

    // 跳过开头的'['
    if (!in.eof() && in.peek() == '[') {
        in.get();  // 读取'['
    }
    // 忽略空格
    while (in.peek() == ' ') {
        in.get();  // 读取空格
    }

    // 循环读取数字直到字符串结束
    while (in >> num) {
        vec.push_back(num);

        // 忽略逗号后的空格
        while (in.peek() == ' ') {
            in.get();  // 读取空格
        }
        // 检查是否还有逗号分隔符
        if (in.peek() == ',') {
            in.get();  // 读取逗号
        }

        // 忽略逗号后的空格
        while (in.peek() == ' ') {
            in.get();  // 读取空格
        }

        if (in.peek() == ']') {
            in.get();
            break;
        }
    }

    return vec;
}

inline std::vector<int> operator"" _vec(const char *str, size_t) {
    std::stringstream ss(str);

    return buildVector(ss);
}

inline std::vector<vector<int>> operator"" _vec2(const char *str, size_t) {
    std::vector<vector<int>> vec;
    std::stringstream ss(str);
    int num = 0;
    while (ss) {
        ss.get();
        vec.push_back(buildVector(ss));
        ss.get();
        if (ss.peek() == -1) {
            break;
        }
    }

    return vec;
}

inline TreeNode *operator"" _tree(const char *str, size_t) {
    std::stringstream ss(str);
    auto vec = buildVector(ss);
    return buildTree(vec);
}

inline ListNode *operator"" _list(const char *str, size_t) {
    std::stringstream ss(str);
    auto vec = buildVector(ss);
    return buildList(vec);
}