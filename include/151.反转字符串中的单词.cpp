/*
 * @lc app=leetcode.cn id=151 lang=cpp
 *
 * [151] 反转字符串中的单词
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    void preprocess(string& s) {
        int left = 0;
        int i = 0;
        while (i < s.size()) {
            // 先经历一段空白
            while (i < s.size()) {
                if (s[i] != ' ') {
                    break;
                }
                i++;
            }
            if (i == s.size()) {
                s.resize(left - 1);
                return;
            }
            // 经历字符
            while (i < s.size()) {
                if (s[i] != ' ') {
                    s[left++] = s[i++];
                } else {
                    break;
                }
            }
            if (i == s.size()) {
                s.resize(left);
                return;
            }
            if (i + 1 >= s.size()) {
                s.resize(left);
                return;
            }
            s[left] = ' ';  //! 必须补个空格

            left = left + 1;
            i = i + 1;
        }
    }
    string reverseWords(string s) {
        preprocess(s);
        std::ranges::reverse(s);
        int begin = 0;
        int i = 0;

        while (i < s.size()) {
            for (; i < s.size(); i++) {
                if (s[i] == ' ') {
                    std::reverse(s.begin() + begin, s.begin() + i);
                    begin = -1;
                    break;
                }
            }
            if (i == s.size() && begin != -1) {
                std::reverse(s.begin() + begin, s.begin() + i);
                begin = -1;
            }
            for (; i < s.size(); i++) {
                if (s[i] != ' ') {
                    begin = i;
                    break;
                }
            }
        }

        return s;
    }
};
// @lc code=end
