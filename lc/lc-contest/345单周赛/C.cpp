class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), dp[n][m];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i) dp[i][0] = 1;
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[j][i] > grid[j][i - 1] && dp[j][i - 1] > 0)
                    dp[j][i] = max(dp[j][i], dp[j][i - 1] + 1);
                if (j - 1 >= 0 && grid[j][i] > grid[j - 1][i - 1] && dp[j - 1][i - 1] > 0) 
                    dp[j][i] = max(dp[j][i], dp[j - 1][i - 1] + 1);
                if (j + 1 < n && grid[j][i] > grid[j + 1][i - 1] && dp[j + 1][i - 1] > 0)
                    dp[j][i] = max(dp[j][i], dp[j + 1][i - 1] + 1);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) ans = max(ans, dp[i][j]);
        return ans - 1;
    }
};