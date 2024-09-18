/*
    算法思路：（只能用于单峰函数)

    初始化：
        设定两个指针，low = 0，high = n - 1，其中 n 是数组的长度。

    二分查找过程：
        当 low < high 时，进行以下步骤：
            计算中间位置：mid = low + (high - low) / 2。
            比较 A[mid] 和 A[mid + 1]：
                如果 A[mid] < A[mid + 1]，说明峰值在右半部分，更新 low = mid + 1。
                否则，峰值在左半部分或就是 mid，更新 high = mid。

    结束条件：
        当 low == high 时，A[low] 即为峰值。
*/
#include <iostream>
#include <vector>

int findPeak(const std::vector<int>& A) {
    int low = 0;
    int high = A.size() - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;

        // 防止数组越界，确保 mid + 1 不超过数组范围
        if (mid + 1 < A.size() && A[mid] < A[mid + 1]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return A[low];
}

int main() {
    std::vector<int> A1 = {7, 7, 7, 5, 3, 3, 3, 5, 7};
    std::vector<int> A2 = {9, 11, 13, 15, 15, 15, 11, 13, 9, 9, 9};
    std::vector<int> A3 = {0, 2, 4, 6, 4, 2, 0};

    std::cout << "峰值为: " << findPeak(A1) << std::endl;  // 输出: 7
    std::cout << "峰值为: " << findPeak(A2) << std::endl;  // 输出: 15
    std::cout << "峰值为: " << findPeak(A3) << std::endl;  // 输出: 6

    return 0;
}
