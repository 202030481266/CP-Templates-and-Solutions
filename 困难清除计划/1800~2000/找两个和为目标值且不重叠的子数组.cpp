class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        // 前缀和是单调增加的
        int sum = 0;
        int l = 0;
        int n = arr.size();

        vector<vector<int>> res;

        for (int i = 0; i < n; ++i) {
            sum += arr[i];
            while (target < sum) 
                sum -= arr[l++];
            if (sum == target)
                res.emplace_back(vector<int>{l, i});
        }

        if (res.size() < 2) return -1;
        int m = res.size();
        int ans = INT_MAX;
        sort(res.begin(), res.end());
        vector<int> dis(m);
        vector<int> left(m);
        vector<int> minn(m + 1, INT_MAX);

        for (int i = 0; i < m; ++i) dis[i] = res[i][1] - res[i][0] + 1;
        for (int i = 0; i < m; ++i) left[i] = res[i][0];
        for (int i = m - 1; i >= 0; --i) minn[i] = min(minn[i + 1], dis[i]);
        for (int i = 0; i < m; ++i) {
            auto nxt = upper_bound(left.begin(), left.end(), res[i][1]);
            if (nxt == left.end()) break;
            int pos = (nxt - left.begin());
            ans = min(ans, dis[i] + minn[pos]);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};