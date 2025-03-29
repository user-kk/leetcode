#include <ios>
#include "common.h"

ENABLE_REDIRECT;

MYTEST_F(1) {
    int m = 0, n = 0;
    cin >> m >> n;

    vector<vector<int>> val(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> val[i][j];
        }
    }
    vector<int> row_prefix_sum(m, 0);  // 按行切分的前缀和
    vector<int> col_prefix_sum(n, 0);  // 按列切分的前缀和

    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            k += val[i][j];
        }
        row_prefix_sum[i] = k;
    }

    k = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            k += val[i][j];
        }
        col_prefix_sum[j] = k;
    }

    int ret = INT_MAX;

    if (m != 1) {
        // 可以按行切分
        for (int i = 0; i < m - 1; i++) {
            ret =
                std::min(ret, std::abs(row_prefix_sum.back() -
                                       row_prefix_sum[i] - row_prefix_sum[i]));
        }
    }
    if (n != 1) {
        // 可以按列切分
        for (int i = 0; i < n - 1; i++) {
            ret =
                std::min(ret, std::abs(col_prefix_sum.back() -
                                       col_prefix_sum[i] - col_prefix_sum[i]));
        }
    }
    cout << ret << endl;
}