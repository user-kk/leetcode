#include <gtest/gtest.h>

#include <initializer_list>
#include <queue>
#include <span>
#include <stack>
#include <string>
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
    ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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