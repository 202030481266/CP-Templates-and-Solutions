class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), dp[n][m][m];
        memset(dp, -1, sizeof(dp));
        dp[0][0][m - 1] = grid[0][0] + grid[0][m - 1];
        for (int i = 0; i < n - 1; ++i) {
            for (int x = 0; x < m; ++x)
                for (int y = 0; y < m; ++y) {
                    if (dp[i][x][y] != -1)
                    for (int a = -1; a <= 1; ++a) 
                        for (int b = -1; b <= 1; ++b) {
                            if (x + a >= 0 && x + a < m && y + b >= 0 && y + b < m) {
                                int tmp = (x + a == y + b ? grid[i + 1][x + a] : grid[i + 1][x + a] + grid[i + 1][y + b]);
                                dp[i + 1][x + a][y + b] = max(dp[i + 1][x + a][y + b], dp[i][x][y] + tmp);
                            }
                        }
                }
        }
        int ans = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j) ans = max(ans, dp[n - 1][i][j]);
        return ans;
    }
};