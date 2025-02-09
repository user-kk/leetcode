/*
 * @lc app=leetcode.cn id=208 lang=cpp
 *
 * [208] 实现 Trie (前缀树)
 */
#include "common.h"

#include <vector>
// @lc code=start
class Trie {
   public:
    struct TrieNode {
        TrieNode() = default;
        explicit TrieNode(char cc) : c(cc) {}
        char c = '\0';
        bool hasWord = false;
        vector<TrieNode*> nexts = {26, nullptr};
    };
    Trie() : root(new TrieNode()) {}
    TrieNode* root = nullptr;
    void insert(string_view word) {
        TrieNode* p = root;
        for (char c : word) {
            if (p->nexts[c - 'a'] == nullptr) {
                p->nexts[c - 'a'] = new TrieNode(c);
            }
            p = p->nexts[c - 'a'];
        }
        p->hasWord = true;
    }

    bool search(string_view word) {
        TrieNode* p = root;
        for (char c : word) {
            if (p->nexts[c - 'a'] == nullptr) {
                return false;
            }
            p = p->nexts[c - 'a'];
        }

        return p->hasWord;
    }

    bool startsWith(string_view prefix) {
        TrieNode* p = root;
        for (char c : prefix) {
            if (p->nexts[c - 'a'] == nullptr) {
                return false;
            }
            p = p->nexts[c - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end
