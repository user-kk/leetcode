/*
 * @lc app=leetcode.cn id=179 lang=cpp
 *
 * [179] 最大数
 */
#include <algorithm>
#include <ranges>
#include <string>
#include "common.h"
// @lc code=start
class Solution {
   public:
    string largestNumber(vector<int>& nums) {
        vector<string> num_strings;
        num_strings.reserve(nums.size());
        size_t len = 0;

        for (int v : nums) {
            num_strings.push_back(std::to_string(v));
            len += num_strings.back().size();
        }

        auto cmp = [](const string& a, const string& b) {
            //! 这里字母序比较的前提：a+b和b+a等长
            return a + b > b + a;
        };

        std::sort(num_strings.begin(), num_strings.end(), cmp);

        string ret;
        ret.reserve(len);
        for (auto& s : num_strings) {
            ret.append(s);
        }

        if (ret[0] == '0') {  // 若排完序后最大的为0，那么结果就是0
            return "0";
        }
        return ret;
    }
};
// @lc code=end
