/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size() + nums2.size();
        if (n % 2 == 1) {
            return findNthV(nums1, nums2, n / 2 + 1);
        } else {
            double t1 = findNthV(nums1, nums2, n / 2);
            double t2 = findNthV(nums1, nums2, n / 2 + 1);
            return (t1 + t2) / 2;
        }
    }

    // 在两个数组中找合并后第k小的值
    int findNthV(vector<int>& nums1, vector<int>& nums2, int k) {
        // 每次都要排除 k/2 个（序号从0到k/2-1）
        // 这个是排除后数组的起始点（新数组的起点）
        //! 后面每次算都要加起始点，别忘了起始点变了！！！
        int s1 = 0;
        int s2 = 0;

        while (true) {
            // 排除些特殊情况
            // 两个数组任一为空时，返回另一个的k序号的值
            if (s1 == nums1.size()) {
                return nums2[s2 + k - 1];
            }

            if (s2 == nums2.size()) {
                return nums1[s1 + k - 1];
            }
            // k为1时，直接返回二者首部最小值(其实是为防止k/2-1为负越界)
            if (k == 1) {
                return std::min(nums1[s1], nums2[s2]);
            }

            // 计算新的k/2-1位置（还要防止k/2-1太大越界，若越界，取最后那个）
            int new_s1 =
                std::min(static_cast<int>(nums1.size()), s1 + k / 2) - 1;
            int new_s2 =
                std::min(+static_cast<int>(nums2.size()), s2 + k / 2) - 1;

            // 小的部分不可能是第k小，直接抹掉
            //! 别忘了调整k
            if (nums1[new_s1] <= nums2[new_s2]) {
                // 从s1到new_s1都是被抹掉的
                k -= (new_s1 - s1 + 1);
                s1 = new_s1 + 1;
            } else {
                k -= (new_s2 - s2 + 1);
                s2 = new_s2 + 1;
            }
        }
    }
};
// @lc code=end
