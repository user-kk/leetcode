/*
 * @lc app=leetcode.cn id=738 lang=cpp
 *
 * [738] 单调递增的数字
 */
#include <algorithm>
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> num2vector(int num) {
        vector<int> ret;
        ret.reserve(9);
        if (num == 0) {
            ret.push_back(0);
            return ret;
        }
        while (num != 0) {
            ret.push_back(num % 10);
            num = num / 10;
        }
        std::ranges::reverse(ret.begin(), ret.end());
        return ret;
    }
    int vector2num(const vector<int> &v) {
        int ret = 0;
        for (int i = 0; i < v.size(); i++) {
            ret = ret * 10 + v[i];
        }
        return ret;
    }
    int monotoneIncreasingDigits(int n) {
        vector<int> num = num2vector(n);
        if (num.size() == 1) {
            return vector2num(num);
        }
        for (int i = 1; i < num.size(); i++) {
            if (num[i - 1] <= num[i]) {
                continue;
            }
            while (i - 1 >= 0 && num[i - 1] > num[i]) {
                num[i - 1]--;
                for (int j = i; j < num.size(); j++) {
                    num[j] = 9;
                }
                i--;
            }
            break;
        }
        return vector2num(num);
    }
};
// @lc code=end
