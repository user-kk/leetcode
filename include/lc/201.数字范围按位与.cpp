/*
 * @lc app=leetcode.cn id=201 lang=cpp
 *
 * [201] 数字范围按位与
 */
#include <bitset>
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 得到翻转版本二进制
    string getReverse2bin(int v) {
        string ret;
        while (v != 0) {
            ret.push_back(v % 2 == 0 ? '0' : '1');
            v = v / 2;
        }
        return ret;
    }
    int rangeBitwiseAnd2(int left, int right) {
        if (left == right) {
            return left;
        }
        string a = getReverse2bin(left);
        string b = getReverse2bin(right);
        if (a.size() != b.size()) {
            return 0;
        }
        std::bitset<32> ret;
        int len = a.size();

        for (int i = len - 1; i >= 0; i--) {
            if (a[i] == b[i] && a[i] == '1') {
                ret.set(i);
            } else if (a[i] == b[i] && a[i] == '0') {
                continue;
            } else {
                break;
            }
        }
        return ret.to_ulong();
    }
    // 本质:找公共前缀
    int rangeBitwiseAnd(int left, int right) {
        bool flag = false;
        int ret = 0;
        for (int i = 31; i >= 0; i--) {
            int left_val = left & (1 << i);
            int right_val = right & (1 << i);
            if (!flag) {
                if (left_val != right_val) {
                    return ret;
                }
                if (left_val != 0) {
                    flag = true;
                    ret = ret | (1 << i);
                }
            } else {
                if (left_val != right_val) {
                    return ret;
                }
                if (left_val != 0) {
                    ret = ret | (1 << i);
                }
            }
        }
        return ret;
    }
};
// @lc code=end
