class Solution {
public:
    int numWays(int n, int k) {
        // 和之前相同颜色或者不同颜色
        vector dp(n, vector<int>(2));
        dp[0][0] = k;
        for (int i = 1; i < n; ++i) {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) * (k - 1);
            dp[i][1] = dp[i - 1][0];
        }
        return dp[n - 1][0] + dp[n - 1][1];
    }
};