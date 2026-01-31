class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int n = nums.size();
        int l = *min_element(nums.begin(), nums.end());
        int r = *max_element(nums.begin(), nums.end());

        auto f = [&](int m) {
            vector<vector<int>> dp(n, vector<int>(2, 0));
            if (nums[0] <= m) dp[0][1] = 1;
            for (int i = 1; i < n; ++i) {
                if (nums[i] <= m) {
                    // can take
                    dp[i][1] = dp[i - 1][0] + 1;
                }
                // can not take
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            }
            return max(dp[n - 1][0], dp[n - 1][1]) >= k;
        };
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (f(mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }
};