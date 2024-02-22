class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size(), m = costs[0].size(), dp[n][m], f[m], g[m];

        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < m; ++i) dp[0][i] = costs[0][i];

        auto update = [&](int x) {
            f[0] = dp[x][0];
            g[m - 1] = dp[x][m - 1];
            for (int i = 1; i < m; ++i) f[i] = min(f[i - 1], dp[x][i]);
            for (int i = m - 2; i >= 0; --i) g[i] = min(g[i + 1], dp[x][i]);
        };
        
        update(0);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j > 0) dp[i][j] = min(dp[i][j], f[j - 1]);
                if (j < m - 1) dp[i][j] = min(dp[i][j], g[j + 1]);
                dp[i][j] += costs[i][j];
            }
            update(i);
        }
        return f[m - 1];
    }
};