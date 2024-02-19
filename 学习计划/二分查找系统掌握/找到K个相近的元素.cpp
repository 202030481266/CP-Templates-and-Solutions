// 此题因为有重复元素的存在，所以O(logn)的算法难度很高
class Solution {
public:
    vector<int> findClosestElements(const vector<int>& arr, int k, int x) {
        int lo = 0, hi = arr.size() - k;
        while (lo < hi) {
            const int mi = (lo + hi) / 2;
            if (x - arr[mi] > arr[mi + k - 1] - x) // 这里将绝对值函数去掉可以解决连续重复的数字问题
                lo = mi + 1;
            else hi = mi;
        }
        if (lo > 0 && abs(arr[lo - 1] - x) <= abs(arr[lo + k - 1] - x))
            --lo;
        return vector<int>(arr.begin() + lo, arr.begin() + lo + k);
    }
};
// 这道题可以看作求一个大小为 k 的区间，使区间内元素与 x 的距离的最大值最小，这个最大值显然只与区间两端点有关，
// 设区间左端点为 i 的话，就是要让max(x - arr[i], arr[i + k - 1] - x)最小。然后注意到x - arr[i]递减，arr[i + k - 1] - x递增，
// 两者的交点就是最小值，用二分可以找到这个交点。