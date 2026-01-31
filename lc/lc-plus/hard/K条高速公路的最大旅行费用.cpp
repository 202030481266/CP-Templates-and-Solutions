class Solution {
public:
    int maximumCost(int n, vector<vector<int>>& h, int k) {
        // 最长简单路径
        int dp[1 << n][n];
        int g[n][n];
        memset(dp, -1, sizeof(dp));
        memset(g, -1, sizeof(g));
        for (int i = 0; i < n; ++i)
            dp[1 << i][i] = 0;
        for (auto& e : h) {
            int u = e[0], v = e[1];
            g[u][v] = g[v][u] = e[2];
        }
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    for (int k = 0; k < n; ++k) {
                        if (g[k][j] != -1 && (i >> k) & 1 && dp[i ^ (1 << j)][k] != -1) {
                            dp[i][j] = max(dp[i][j], dp[i ^ (1 << j)][k] + g[k][j]);
                        }
                    }
                }
            }
        }
        int ans = -1;
        for (int i = 1; i < (1 << n); ++i)
            if (__builtin_popcount(i) == k + 1)
                for (int j = 0; j < n; ++j)
                    ans = max(ans, dp[i][j]);
        return ans;
    }
};