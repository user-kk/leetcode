/*
 * @lc app=leetcode.cn id=79 lang=cpp
 *
 * [79] 单词搜索
 */
#include <common.h>

#include <type_traits>
// @lc code=start
class Solution {
   public:
    int m;
    int n;
    vector<vector<bool>> visited;
    bool dfs(const vector<vector<char>>& board, const string& word, int i,
             int j, int depth) {
        if (depth >= word.size() || i < 0 || i >= m || j < 0 || j >= n ||
            board[i][j] != word[depth] || visited[i][j]) {
            return false;
        }
        if (depth == word.size() - 1) {
            return true;
        }
        visited[i][j] = true;
        if (dfs(board, word, i - 1, j, depth + 1)) {
            return true;
        }
        if (dfs(board, word, i, j + 1, depth + 1)) {
            return true;
        }
        if (dfs(board, word, i + 1, j, depth + 1)) {
            return true;
        }
        if (dfs(board, word, i, j - 1, depth + 1)) {
            return true;
        }
        visited[i][j] = false;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        visited.assign(m, std::vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end
