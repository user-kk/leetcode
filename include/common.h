#include <gtest/gtest.h>

#include <algorithm>
#include <initializer_list>
#include <numeric>
#include <queue>
#include <span>
#include <stack>
#include <string>
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

inline TreeNode *buildTree(std::initializer_list<int> list) {
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

inline ListNode *buildList(std::initializer_list<int> list) {
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