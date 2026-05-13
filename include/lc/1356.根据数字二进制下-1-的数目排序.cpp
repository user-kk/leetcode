/*
 * @lc app=leetcode.cn id=1356 lang=cpp
 *
 * [1356] 根据数字二进制下 1 的数目排序
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> sortByBits(vector<int>& arr) {
        struct T {
            int count;
            int val;
        };
        vector<T> k;
        k.reserve(arr.size());

        for (int v : arr) {
            T t{0, v};

            while (v > 0) {
                // v大于0，所以肯定有一位有1
                // 查1的个数时可考虑用 v&v-1
                t.count++;
                v = v & (v - 1);
            }
            k.push_back(t);
        }

        std::sort(k.begin(), k.end(), [](const T& a, const T& b) {
            if (a.count != b.count) {
                return a.count < b.count;
            }
            return a.val < b.val;
        });
        vector<int> ret;
        ret.reserve(arr.size());
        for (auto& i : k) {
            ret.push_back(i.val);
        }
        return ret;
    }
};
// @lc code=end
