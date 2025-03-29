/*
 * @lc app=leetcode.cn id=454 lang=cpp
 *
 * [454] 四数相加 II
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    struct MyMap {
        std::unordered_map<int, int> m;
        void push(int v) {
            if (auto it = m.find(v); it != m.end()) {
                it->second++;
            } else {
                m[v] = 1;
            }
        }
    };
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3,
                     vector<int>& nums4) {
        MyMap k;
        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0; j < nums2.size(); j++) {
                k.push(nums1[i] + nums2[j]);
            }
        }
        int ret = 0;

        for (int i = 0; i < nums3.size(); i++) {
            for (int j = 0; j < nums4.size(); j++) {
                if (auto it = k.m.find(-(nums3[i] + nums4[j]));
                    it != k.m.end()) {
                    ret += it->second;
                }
            }
        }
        return ret;
    }
};
// @lc code=end
