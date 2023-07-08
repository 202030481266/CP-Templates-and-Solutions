class Solution {
    int dp[100010], sum[100010], f[100010];
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        memset(dp, -0x3f, sizeof(dp));
        memset(f, -0x3f, sizeof(f));
        for (int i = 0; i < n; ++i) 
            sum[i + 1] = sum[i] + stones[i];
        if (n == 2) return sum[n];
        dp[n + 1] = 0;
        f[n] = max(f[n + 1], sum[n] - dp[n + 1]);
        for (int i = n; i >= 2; --i) {
            dp[i] = f[i];
            f[i - 1] = max(f[i], sum[i - 1] - dp[i]);
        }
        int ans = INT_MIN;
        for (int i = 2; i <= n; ++i)
            ans = max(ans, sum[i] - dp[i + 1]);
        return ans;
    }
};