class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        // 位置i中表明缺失了arr[i] - (i + 1)个数字
        int l = -1, r = arr.size() - 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (arr[mid] - (mid + 1) >= k) r = mid;
            else l = mid;
        }
        // r 就是最左边的满足缺失数字大于等于k的索引
        if (arr[r] - (r + 1) < k) {
            int loss = arr[r] - (r + 1);
            return arr[r] + (k - loss);
        }
        else if (r == 0) return k;
        else {
            int pre = arr[r - 1] - r;
            return arr[r - 1] + (k - pre);
        }
    }
};