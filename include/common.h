#include <gtest/gtest.h>

#include <algorithm>
#include <cstdio>
#include <initializer_list>
#include <numeric>
#include <queue>
#include <span>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

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
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

inline std::vector<int> buildVector(const std::string &s) {
    json j = json::parse(s);

    // 检查是否为数组
    if (!j.is_array()) {
        throw std::runtime_error("not vector");
    }

    // 将 JSON 数组转换为 std::vector<int>
    std::vector<int> vec = j.get<std::vector<int>>();

    return vec;
}

inline std::vector<std::vector<int>> build2dVector(const std::string &s) {
    json j = json::parse(s);

    // 检查是否为数组
    if (!j.is_array()) {
        throw std::runtime_error("not vector");
    }

    auto vec = j.get<std::vector<std::vector<int>>>();

    return vec;
}

inline std::vector<int> operator"" _vec(const char *str, size_t) {
    return buildVector(str);
}

inline std::vector<vector<int>> operator"" _vec2(const char *str, size_t) {
    return build2dVector(str);
}

inline TreeNode *operator"" _tree(const char *str, size_t) {
    auto vec = buildVector(str);
    return buildTree(vec);
}

inline ListNode *operator"" _list(const char *str, size_t) {
    auto vec = buildVector(str);
    return buildList(vec);
}