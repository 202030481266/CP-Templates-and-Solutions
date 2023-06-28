class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size(), dp[n][2];
        memset(dp, -0x3f, sizeof(dp));
        dp[0][0] = arr[0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(0, dp[i - 1][0]) + arr[i];
            dp[i][1] = max(dp[i - 1][1] + arr[i], dp[i - 1][0]);
        }
        int ans = -0x3f3f3f3f;
        for (int i = 0; i < n; ++i) 
            ans = max(ans, max(dp[i][0], dp[i][1]));
        return ans;
    }
};