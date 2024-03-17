class Solution {
public:
    long long minimumMoves(vector<int>& nums, int k, int maxChanges) {
        // k > maxChanges
        // Min(abs(x-yi)) 就是中位数
        int n = nums.size();
        vector<int> cost(3);
        for (int i = 0; i < n; ++i) {
            if (nums[i]) {
                cost[0] = 1;
                if (i - 1 >= 0 && i + 1 < n && nums[i - 1] && nums[i + 1]) cost[2] = 3;
                else if (i - 1 >= 0 && nums[i - 1]) cost[1] = 2;
                else if (i + 1 < n && nums[i + 1]) cost[1] = 2;
            }
        }
        int mx = 0;
        for (int i = 0; i < 3; ++i) 
            if (cost[i]) mx = i + 1;
        // mx >= k
        if (k <= mx) return cost[k - 1] - 1;
        if (k <= mx + maxChanges) {
            if (mx > 0)
                return cost[mx - 1] - 1 + (k - mx) * 2;
            else return k * 2;
        }

        // 维护一个 k - maxChanges 的窗口，然后维护其中的中位数
        // 不过因为是本来就是有序的，所以会很简单
        vector<int> index;
        for (int i = 0; i < n; ++i) 
            if (nums[i]) index.push_back(i);
        vector<long long> sum(index.size() + 1);
        for (int i = 0; i < index.size(); ++i)
            sum[i + 1] = sum[i] + index[i];
        int len = k - maxChanges;
        long long ans = LONG_LONG_MAX;
        for (int i = 0; i + len - 1 < index.size(); ++i) {
            // cout << i << endl;
            int mid = (i + len - 1 + i) / 2;
            // [i, mid] is left
            // [mid + 1, i + len - 1] is right
            long long x = sum[mid + 1] - sum[i], y = sum[i + len] - sum[mid + 1];
            long long left = (mid - i + 1), right = (i + len - 1 - mid);
            ans = min(ans, -x + y + (left - right) * index[mid]);
        }
        return ans + maxChanges * 2;
    }
};