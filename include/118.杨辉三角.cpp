/*
 * @lc app=leetcode.cn id=118 lang=cpp
 *
 * [118] 杨辉三角
 */
#include <common.h>
// @lc code=start
class Solution {
   public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        ret.reserve(numRows);
        for (int i = 0; i < numRows; i++) {
            vector<int> t;
            t.resize(i + 1);
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    t[j] = 1;
                    continue;
                }
                t[j] = ret[i - 1][j - 1] + ret[i - 1][j];
            }
            ret.emplace_back(std::move(t));
        }
        return ret;
    }
};
// @lc code=end
