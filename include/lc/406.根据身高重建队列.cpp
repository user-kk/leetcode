/*
 * @lc app=leetcode.cn id=406 lang=cpp
 *
 * [406] 根据身高重建队列
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        //! 身高高的在前面(方便知道前面有几个比我大的)，要求少的在前面
        std::sort(people.begin(), people.end(),
                  [](const vector<int>& a, const vector<int>& b) {
                      if (a[0] < b[0]) {
                          return false;
                      } else if (a[0] > b[0]) {
                          return true;
                      } else {
                          return a[1] < b[1];
                      }
                  });
        list<vector<int>> li;
        vector<vector<int>> ret;
        for (auto& v : people) {
            auto pos = v[1];
            auto it = li.begin();
            for (int i = 0; i < pos; i++) {
                it++;
            }
            li.insert(it, v);
        }

        return {li.begin(), li.end()};
    }
};
// @lc code=end
