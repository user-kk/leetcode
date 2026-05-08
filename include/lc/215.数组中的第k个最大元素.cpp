/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */
#include "common.h"
#include <cstdlib>
#include <ctime>

namespace {
// 小根堆
struct Heap {
    vector<int> vals;

    explicit Heap(vector<int> v) : vals(std::move(v)) {
        //! 从最后一个非叶子节点开始下沉,记住要下沉，不是调整下就不管了，要下沉！！
        for (int i = vals.size() / 2 - 1; i >= 0; i--) {
            siftDown(i);
        }
    }

    bool empty() const { return vals.empty(); }

    int top() {
        return empty() ? -1 : vals[0];  // 或抛异常
    }

    void pop() {
        if (empty()) {
            return;
        }
        vals[0] = vals.back();
        vals.pop_back();
        if (!empty()) {
            siftDown(0);
        }
    }

   private:
    // 下沉：把i位置元素放到正确位置
    void siftDown(int i) {
        while (true) {
            int minIdx = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < vals.size() && vals[left] < vals[minIdx]) {
                minIdx = left;
            }

            if (right < vals.size() && vals[right] < vals[minIdx]) {
                minIdx = right;
            }

            if (minIdx == i) {
                break;
            }

            swap(vals[i], vals[minIdx]);
            i = minIdx;  // 继续往下
        }
    }
};

// @lc code=start
class Solution {
   public:
    Solution() { std::srand(time(nullptr)); }
    int findKthLargest(std::vector<int>& nums, int k) {
        return findKthLargest(nums, 0, nums.size() - 1, nums.size() - k);
    }
    // 快排写法的问题 ，标准答案中没有等号，导致一个极端例子很快nums[r] >= t
    int findKthLargest(std::vector<int>& nums, int first, int last, int k) {
        std::swap(nums[first], nums[first + (last - first) / 2]);
        int t = nums[first];
        int l = first;
        int r = last;
        while (l < r) {
            while (l < r && nums[r] >= t) {
                r--;
            }
            nums[l] = nums[r];

            while (l < r && nums[l] <= t) {
                l++;
            }
            nums[r] = nums[l];
        }
        nums[l] = t;

        if (l < k) {
            return findKthLargest(nums, l + 1, last, k);
        } else if (l > k) {
            return findKthLargest(nums, first, l - 1, k);
        } else {
            return t;
        }
    }

    //! 快排模板
    int findKthLargest2(std::vector<int>& nums, int first, int last, int k) {
        if (first == last) {
            return nums[first];
        }

        swap(nums[first], nums[first + std::rand() % (last - first + 1)]);

        int val = nums[first];
        int i = first;
        int j = last;

        while (i < j) {
            while (i < j && nums[j] >= val) {
                j--;
            }
            while (i < j && nums[i] <= val) {
                i++;
            }

            swap(nums[i], nums[j]);
        }

        //! 此时i==j, 别忘把枢轴量换过来
        swap(nums[first], nums[i]);
        if (i == k) {
            return nums[i];
        } else if (i < k) {
            return findKthLargest2(nums, i + 1, last, k);
        } else {
            return findKthLargest2(nums, first, i - 1, k);
        }
    }

    int findKthLargest3(std::vector<int>& nums, int k) {
        Heap h(nums);

        for (int i = 0; i < nums.size() - k; i++) {
            h.pop();
        }
        return h.top();
    }
};
// @lc code=end
}  // namespace
