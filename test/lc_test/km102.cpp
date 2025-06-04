#include "common.h"
#include "debug_macro.hpp"

namespace {
struct Pos {
    int i;
    int j;
};

bool isValid(Pos pos, int n, int m) {
    return pos.i >= 0 && pos.i < n && pos.j >= 0 && pos.j < m;
}

void bfs(std::vector<std::vector<int>>& g, int n, int m, Pos start,
         int set_val) {
    g[start.i][start.j] = set_val;
    std::queue<Pos> q;

    q.push(start);

    while (!q.empty()) {
        Pos p = q.front();
        q.pop();
        Pos top{p.i - 1, p.j};
        Pos down{p.i + 1, p.j};
        Pos left{p.i, p.j - 1};
        Pos right{p.i, p.j + 1};
        if (isValid(top, n, m) && g[top.i][top.j] == 1) {
            g[top.i][top.j] = set_val;
            q.push(top);
        }
        if (isValid(down, n, m) && g[down.i][down.j] == 1) {
            g[down.i][down.j] = set_val;
            q.push(down);
        }
        if (isValid(left, n, m) && g[left.i][left.j] == 1) {
            g[left.i][left.j] = set_val;
            q.push(left);
        }
        if (isValid(right, n, m) && g[right.i][right.j] == 1) {
            g[right.i][right.j] = set_val;
            q.push(right);
        }
    }
}
}  // namespace

ENABLE_REDIRECT;

MYTEST_F(1) {
    int n = 0, m = 0;
    cin >> n >> m;
    std::vector<std::vector<int>> g(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        if (g[0][i] == 1) {
            bfs(g, n, m, {0, i}, 2);
        }
    }
    for (int i = 0; i < m; i++) {
        if (g[n - 1][i] == 1) {
            bfs(g, n, m, {n - 1, i}, 2);
        }
    }
    for (int i = 0; i < n; i++) {
        if (g[i][0] == 1) {
            bfs(g, n, m, {i, 0}, 2);
        }
    }
    for (int i = 0; i < n; i++) {
        if (g[i][m - 1] == 1) {
            bfs(g, n, m, {i, m - 1}, 2);
        }
    }

    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            if (g[i][j] == 1) {
                bfs(g, n, m, {i, j}, 0);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 2) {
                cout << 1 << ' ';
            } else {
                cout << g[i][j] << ' ';
            }
        }
        cout << endl;
    }
}