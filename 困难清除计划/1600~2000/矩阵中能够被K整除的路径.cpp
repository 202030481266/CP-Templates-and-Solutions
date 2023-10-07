class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size(), dp[n + 1][m + 1][k];
        memset(dp, 0, sizeof(dp));
        dp[1][1][grid[0][0] % k] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) 
                for (int x = 0; x < k; ++x) {
                    int& tmp = dp[i][j][(x + grid[i - 1][j - 1]) % k];
                    tmp = (tmp + (dp[i - 1][j][x] + dp[i][j - 1][x]) % mod) % mod;
                }
        return dp[n][m][0];
    }
};