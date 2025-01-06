/*
 * @lc app=leetcode.cn id=71 lang=cpp
 *
 * [71] 简化路径
 */
#include <common.h>
N_B
    // @lc code=start
    class Solution {
   public:
    struct T {
        string content;
        bool commited = false;
    };
    void submit(deque<T>& q) {
        if (q.empty() || q.back().commited) {
            return;
        }

        if (q.back().content.size() > 2) {
            q.back().commited = true;
            return;
        }

        if (q.back().content.size() == 1 && q.back().content[0] == '.') {
            q.pop_back();
            return;
        }

        if (q.back().content[0] == '.' && q.back().content[1] == '.') {
            q.pop_back();
            if (!q.empty()) {
                q.pop_back();
            }
            return;
        }
        q.back().commited = true;
    }
    string simplifyPath(string& path) {
        deque<T> q;
        for (char c : path) {
            switch (c) {
                case '/': {
                    submit(q);
                    break;
                }
                default: {
                    if (q.empty() || q.back().commited) {
                        q.emplace_back();
                        q.back().content.push_back(c);
                    } else {
                        q.back().content.push_back(c);
                    }
                    break;
                }
            }
        }
        submit(q);
        string ret;
        ret.reserve(path.size());
        for (auto& i : q) {
            ret.push_back('/');
            ret.append(i.content);
        }
        if (ret.empty()) {
            ret.push_back('/');
        }
        return ret;
    }
};

// @lc code=end
N_E
