/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根
 */
#include "common.h"
// @lc code=start
class Solution {
   public:
    // 二分模板
    int t(vector<int>& nums) {
        auto cond = []([[maybe_unused]] int mid) { return true; };
        // 这个地方根据向左取整还是向右取整来设置，向左取整左闭右开，找不到时为left=right=size()
        // 向右取整左开右闭，找不到时left=right=-1
        int left = -1;
        int right = nums.size() - 1;

        // 开区间，循环出口一定是left==right
        while (left < right) {
            // 从下方可知left可能不变，所以这个地方必须向上取整，即left,right的mid为right而不是left
            // 向下取整时会导致这样的死循环:mid(left,right)=left,left=mid
            // right可能不变时向下取整
            int mid = left + (right - left + 1) / 2;
            // 假设满足条件的在左面，在满足条件中找最大的
            if (cond(nums[mid])) {
                // 满足条件,想找更大的只能调整left，但是left不能调整成mid+1,因为mid+1不一定满足条件
                left = mid;
            } else {
                // 不满足条件，应该往左侧调整，right已经不满足
                // 所以right = mid -1

                right = mid - 1;
            }
        }
        return left;
    }
    int mySqrt(long long x) {
        long long left = -1;
        long long right = x;
        // 条件：找a*a<=x的最大a值
        while (left < right) {
            long long mid = left + (right - left + 1) / 2;
            if (mid * mid <= x) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return left;
    }
};
// @lc code=end
