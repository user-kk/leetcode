/*
 * @lc app=leetcode.cn id=211 lang=cpp
 *
 * [211] 添加与搜索单词 - 数据结构设计
 */
#include <memory>
#include "common.h"
// @lc code=start
class WordDictionary {
   private:
    struct Trie {
        char c;
        bool has;
        std::array<unique_ptr<Trie>, 26> children;
    };
    Trie trie{'\0', true, {}};

   public:
    WordDictionary() {}

    void addWord(const string& word) {
        Trie* p = &trie;
        for (char c : word) {
            if (p->children[c - 'a'] == nullptr) {
                p->children[c - 'a'] = make_unique<Trie>(Trie{c, false, {}});
            }
            p = p->children[c - 'a'].get();
        }
        p->has = true;
    }

    bool search(const string& word) {
        vector<Trie*> q;
        q.push_back(&trie);

        for (char c : word) {
            vector<Trie*> new_q;

            for (int i = 0; i < q.size(); i++) {
                if (c != '.') {
                    if (q[i]->children[c - 'a'] == nullptr) {
                        continue;
                    }
                    new_q.push_back(q[i]->children[c - 'a'].get());
                } else {
                    for (int j = 0; j < 26; j++) {
                        if (q[i]->children[j] != nullptr) {
                            new_q.push_back(q[i]->children[j].get());
                        }
                    }
                }
            }
            q.swap(new_q);
            if (q.empty()) {
                return false;
            }
        }

        if (q.empty()) {
            return false;
        }
        for (int i = 0; i < q.size(); i++) {
            if (q[i]->has) {
                return true;
            }
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
// @lc code=end
