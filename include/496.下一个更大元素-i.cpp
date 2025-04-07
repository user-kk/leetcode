/*
 * @lc app=leetcode.cn id=496 lang=cpp
 *
 * [496] 下一个更大元素 I
 */
#include <unordered_map>
#include "common.h"
// @lc code=start
class Solution {
   public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        std::unordered_map<int, int> m;
        std::deque<int> q;
        q.push_back(nums2.back());
        m[nums2.back()] = -1;
        for (int i = static_cast<int>(nums2.size()) - 2; i >= 0; i--) {
            while (!q.empty() && q.back() <= nums2[i]) {
                q.pop_back();
            }
            if (q.empty()) {
                m[nums2[i]] = -1;
            } else {
                m[nums2[i]] = q.back();
            }

            q.push_back(nums2[i]);
        }
        vector<int> ret;
        ret.reserve(nums1.size());
        for (auto i : nums1) {
            ret.push_back(m[i]);
        }
        return ret;
    }
};
// @lc code=end
