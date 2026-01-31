// 此题因为有重复元素的存在，所以O(logn)的算法难度很高
class Solution {
public:
    vector<int> findClosestElements(const vector<int>& arr, int k, int x) {
        int l = -1, r = arr.size() - k;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (x - arr[mid] > arr[mid + k - 1] - x) 
                l = mid;
            else r = mid;
        }
        if (r > 0 && x - arr[r - 1] <= arr[r + k - 1] - x) --r;
        return vector<int>(arr.begin() + r, arr.begin() + r + k);
    }
};
// 这道题可以看作求一个大小为 k 的区间，使区间内元素与 x 的距离的最大值最小，这个最大值显然只与区间两端点有关，
// 设区间左端点为 i 的话，就是要让max(x - arr[i], arr[i + k - 1] - x)最小。然后注意到x - arr[i]递减，arr[i + k - 1] - x递增，
// 两者的交点就是最小值，用二分可以找到这个交点。