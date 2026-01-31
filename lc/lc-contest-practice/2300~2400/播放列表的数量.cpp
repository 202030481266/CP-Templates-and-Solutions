class Solution {
    static const int mod = 1e9 + 7; 
    typedef long long ll;
    ll dp[110][110];
public:
    int numMusicPlaylists(int n, int goal, int k) {
        // 此动态规划非常巧妙
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= goal; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] += dp[i - 1][j - 1] * (n - j + 1);
                dp[i][j] += dp[i - 1][j] * max(j - k, 0);
                dp[i][j] %= mod;
            }
        }
        return dp[goal][n];
    }
};