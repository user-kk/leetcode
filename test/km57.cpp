#include "common.h"

MYTEST(1) {
    int target = 0, m = 0;
    cin >> target;
    cin >> m;

    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= target; i++) {
        for (int j = 1; j <= m; j++) {
            if (i - j >= 0) {
                dp[i] += dp[i - j];
            }
        }
    }
    cout << dp[target] << endl;
}