/*
 * @lc app=leetcode.cn id=204 lang=cpp
 *
 * [204] 计数质数
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 这个适合求一个质数
    bool isPrime(int v) {
        if (v == 0 || v == 1) {
            return false;
        }
        if (v == 2 || v == 3) {
            return true;
        }

        if (v % 2 == 0 || v % 3 == 0) {
            return false;
        }

        for (int i = 5; i * i <= v; i += 6) {
            // i代表6k-1,i+2代表6k+1,只有这两种可能为质数
            // 6k 6k+2 6k+4为偶
            // 6k+3能被3整除 6k+5为6(k+1)-1

            if (v % i == 0 || v % (i + 2) == 0) {
                return false;
            }
        }
    }
    // 下面的埃式塞适合批量求质数
    int countPrimes(int n) {
        if (n == 0) {
            return 0;
        }
        vector<bool> is_p(n, true);

        // 0和1既不是质数也不是合数
        is_p[0] = false;
        is_p[1] = false;

        for (int i = 2; i * i < n; i++) {
            if (is_p[i]) {
                // 从i*i开始标记，因为之前的被更小的数标记完了
                for (int j = i * i; j < n; j += i) {
                    is_p[j] = false;
                }
            }
        }

        return std::count(is_p.begin(), is_p.end(), true);
    }
};
// @lc code=end
