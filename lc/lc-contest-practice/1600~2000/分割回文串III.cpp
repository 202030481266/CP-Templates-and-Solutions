class Solution {
public:
    int palindromePartition(string s, int k) {
        int n = s.size(), f[n + 1][n + 1], dp[n + 1][k + 1];
        memset(f, 0, sizeof(f));
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < n; ++j) {
                int l = i, r = j;
                while (l < r) if (s[l++] != s[r--]) ++f[i + 1][j + 1];
            }
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = f[1][i];
            for (int x = 2; x <= min(k, i); ++x) {
                for (int j = x; j <= i; ++j)
                    dp[i][x] = min(dp[i][x], dp[j - 1][x - 1] + f[j][i]);
            }
        }
        return dp[n][k];
    }
};