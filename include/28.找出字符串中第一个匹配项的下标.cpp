/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 找出字符串中第一个匹配项的下标
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> getNextArray(const string &s) {
        // next数组的含义为 失配时模式串的下一个回溯位置
        // 例 模式串为s,s[3]失配了,则s[next[3]]就是下一个要比较的位置
        // 这个位置实际上是部分匹配前缀的下一个位置
        //  s 01234
        // 如 ababc  c失配了
        // 看abab的部分匹配值,部分匹配值为2,代表部分匹配前缀(即ab)的长度为2
        // 下一个要匹配的就是s[2],c的索引为4 所以next[4]=2

        if (s.empty()) {
            return {};
        }
        // next数组的第一项必然为-1(如果字符串索引从1开始则为0)
        // 表示如果第一项都不匹配,则不用回溯模式串,主串前进一位
        if (s.size() == 1) {
            return {-1};
        }

        vector<int> next(s.size());
        next[0] = -1;
        // next 数组的第二项必然为0,因为一个字母没有重复前后缀序列
        next[1] = 0;

        size_t repeatPrefixIndex = 0;  // 重复前缀的末尾索引
        size_t sIndex = 1;             // 字符串s的索引
        while (sIndex + 1 < s.size()) {
            // repeatPrefixIndex等于零时并且还不相等时
            // 已经到最前面了,无法回溯去找next了,直接赋值0
            if (repeatPrefixIndex == 0 && s[repeatPrefixIndex] != s[sIndex]) {
                sIndex++;
                next[sIndex] = 0;
                continue;
            }
            // 如果相等了
            if (s[repeatPrefixIndex] == s[sIndex]) {
                repeatPrefixIndex++;
                sIndex++;
                next[sIndex] = (int)repeatPrefixIndex;
            } else {  // 如果不等并且repeatPrefixIndex不为零
                      //  尝试回溯next,下一次循环再次比较
                repeatPrefixIndex = next[repeatPrefixIndex];
            }
        }
        return next;
    }

    vector<int> getNextValArray(const string &s) {
        // nextVal数组的含义为 失配时模式串的下一个回溯位置,与next数组相似
        //          0123   0123
        // 不同点是当aaab 与aaaa比较时
        // b失配 j只回溯到了索引为2的a上,然后又失配 回溯到索引为1的a上
        // 但实际上这些回溯没有意义 因为第一步就比较出了a!=b
        // 问题出在了p[j]和p[next[j]]相等这个情况上,想相等了就不用再次比较了,应该继续回溯直至不等
        // 所以使用nextVal数组

        if (s.empty()) {
            return {};
        }
        if (s.size() == 1) {
            return {-1};
        }

        vector<int> nextVal(s.size());
        nextVal[0] = -1;
        nextVal[1] = 0;
        int repeatPrefixIndex = 0;
        int sIndex = 1;
        while (sIndex + 1 < s.size()) {
            if (repeatPrefixIndex == 0 && s[repeatPrefixIndex] != s[sIndex]) {
                sIndex++;
                nextVal[sIndex] = 0;
                continue;
            }
            // 如果相等了
            if (s[repeatPrefixIndex] == s[sIndex]) {
                repeatPrefixIndex++;
                sIndex++;
                // 看一眼p[j]和p[next[j]]是否相等
                // s[sIndex]为p[j]
                // s[repeatPrefixIndex]为p[next[j]]
                if (s[sIndex] != s[repeatPrefixIndex]) {
                    nextVal[sIndex] = repeatPrefixIndex;
                } else {
                    // 如果相等,回退成 next[next[j]]
                    // 回退一下即可,因为p[j]一定不等于p[next[next[j]]]
                    // 因为如果等了next[next[j]]一定不会被生成
                    nextVal[sIndex] = nextVal[repeatPrefixIndex];
                }
            } else {
                repeatPrefixIndex = nextVal[repeatPrefixIndex];
            }
        }
        return nextVal;
    }

    int strStr(const string &haystack,
               const string &needle) {  // s 主串 patternStr 模式串

        vector<int> next = getNextArray(needle);
        int i = 0;  // i 为主串索引
        int j = 0;  // j 为模式串索引
        while (i < haystack.size() && j < needle.size()) {
            if (j == 0 && haystack[i] != needle[j]) {
                i++;  // j不动 i直接找下一个
                continue;
            }

            if (haystack[i] == needle[j]) {
                i++;
                j++;
            } else {  // 如果不等并且j不是0,使用next数组将j回溯 i不回溯
                j = next[j];
            }
        }
        if (j >= needle.size()) {  // j全部被比较完了
            return i - j;
        }
        return -1;
    }
};
// @lc code=end
