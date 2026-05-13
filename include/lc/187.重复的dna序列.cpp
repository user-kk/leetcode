/*
 * @lc app=leetcode.cn id=187 lang=cpp
 *
 * [187] 重复的DNA序列
 */
#include <cstdint>
#include "common.h"
// @lc code=start
class Solution {
   public:
    //! 位运算 用|和1置位 用&和0清位
    //! 被 清/置 的位用 1<<n 选定
    //! 若同时 清/置 多个位，用十六进制<<n选定
    //! 最好用无符号，有符号的右移是代数右移
    //! 快速得知1的个数：计算n=n&n-1能运行几次才为0
    //! 快速找最低位的1：x&-x (利用了补码，需要是有符号数)
    //! 位运算注意要经常使用(),注意运算符优先级
    vector<string> findRepeatedDnaSequences(string& s) {
        if (s.size() <= 10) {
            return {};
        }
        int m[32] = {0};
        m['A' - 'A'] = 0;
        m['C' - 'A'] = 1;
        m['G' - 'A'] = 2;
        m['T' - 'A'] = 3;

        std::unordered_map<uint32_t, int> vals;
        uint32_t v = 0;
        for (int i = 0; i < 10; i++) {
            v = (v << 2) | m[s[i] - 'A'];
        }

        vals[v]++;

        for (int i = 1; i + 9 < s.size(); i++) {
            v = (v << 2) | m[s[i + 9] - 'A'];
            v = v & 0xfffff;
            vals[v]++;
        }

        vector<string> ret;
        for (auto [v, count] : vals) {
            if (count > 1) {
                string s;
                s.reserve(10);
                for (int i = 0; i < 10; i++) {
                    // 取对应位
                    uint32_t t = (v >> (2 * (9 - i))) & 3;
                    if (t == 0) {
                        s.push_back('A');
                    } else if (t == 1) {
                        s.push_back('C');
                    } else if (t == 2) {
                        s.push_back('G');
                    } else if (t == 3) {
                        s.push_back('T');
                    };
                }
                ret.push_back(std::move(s));
            }
        }
        return ret;
    }
};
// @lc code=end
