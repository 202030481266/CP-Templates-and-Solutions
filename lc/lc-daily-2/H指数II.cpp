class Solution {
public:
    int hIndex(vector<int>& arr) {
        // 升序的算法

        // max(min(arr[i], n - i))
        int n = arr.size();

        // find the first one that arr[i] >= n - i, arr[i] - n + i >= 0 这是一个单调递增的函数
        int l = 0, r = n - 1, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (arr[mid] + mid >= n) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        if (ans == -1) return 0;
        int tmp = (ans > 0 ? arr[ans - 1] : 0);
        return max(tmp, n - ans);
    }
};