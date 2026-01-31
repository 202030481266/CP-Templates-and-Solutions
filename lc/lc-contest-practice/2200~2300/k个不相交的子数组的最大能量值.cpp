// 动态规划 + 前缀最大优化
// 这道题目真的没啥难度，主要是要注意到 n * k <= 10 ^ 6 即可
class Solution {
public:
    long long maximumStrength(vector<int>& nums, int k) {
        int n = nums.size();
        long long dp[n + 1][k + 1], f[k + 1], g[k + 1];
        memset(dp, -0x3f, sizeof(dp));
        memset(f, -0x3f, sizeof(f));
        memset(g, -0x3f, sizeof(g));

        // 前缀和
        vector<long long> sum(n + 1);
        for (int i = 0; i < n; ++i)
            sum[i + 1] = sum[i] + nums[i];
        for (int i = 0; i <= n; ++i) dp[i][0] = 0;
        f[0] = g[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= min(i, k); ++j) {
                if (j & 1) dp[i][j] = f[j - 1] + (k - j + 1) * sum[i];
                else dp[i][j] = g[j - 1] - (k - j + 1) * sum[i];
            }
            for (int j = 0; j <= min(i, k); ++j) {
                f[j] = max(f[j], dp[i][j] - (k - j) * sum[i]);
                g[j] = max(g[j], dp[i][j] + (k - j) * sum[i]);
            }
        }
        long long ans = LONG_LONG_MIN;
        for (int i = k; i <= n; ++i) ans = max(ans, dp[i][k]);
        return ans;
    }
};