#include <vector>

#include "215.数组中的第k个最大元素.cpp"

MYTEST(1) {
    Solution s;
    vector<int> kk{3, 2, 1, 5, 6, 4};
    s.findKthLargest(kk, 2);
}

MYTEST(2) {
    Solution s;
    vector<int> kk{3, 2, 3, 1, 2, 4, 5, 5, 6};
    s.findKthLargest(kk, 4);
}

int quick_sort_sub(vector<int> &a, int low, int high) {
    int t = a[low];  // 第一个数作为枢轴量,将其提取到t中
    while (low < high) {
        for (; low < high && t <= a[high];
             high--);  // 从high开始向后寻找(high不能小于low) 找到比枢轴量小的
        a[low] = a[high];  // 赋给low
        for (; low < high && t >= a[low];
             low++);  // 再从low开始向前寻找(low不能大于high) 找到比枢轴量大的
        a[high] = a[low];  // 赋给high
    }
    a[low] = t;  // 出循环时low=high 将枢轴量放到中间位置
    return low;  // 返回枢轴量的索引
}
void quick_sort(vector<int> &a, int low,
                int high)  // 快速排序 O(nlogn) 不稳定 是一趟到位
                           // 初始序列的不同不会影响算法效率
{
    if (low < high) {
        int mid = quick_sort_sub(a, low, high);
        quick_sort(a, low, mid - 1);
        quick_sort(a, mid + 1, high);
    }
}

MYTEST(3) {
    vector<int> kk{3, 2, 3, 1, 2, 4, 5, 5, 6};
    quick_sort(kk, 0, kk.size() - 1);
}

MYTEST(4) {
    Solution s;
    vector<int> kk{5, 2, 4, 1, 3, 6, 0};
    s.findKthLargest(kk, 4);
}