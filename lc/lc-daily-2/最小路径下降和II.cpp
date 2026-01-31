class Solution {
    int dp[210][210];
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < n; ++i) dp[0][i] = grid[0][i];
        for (int i = 1; i < n; ++i) 
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (j != k) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][k]);
                    }
                }
                dp[i][j] += grid[i][j];
            }
        int ans = INT_MAX;
        for (int i = 0; i < n; ++i) ans = min(ans, dp[n - 1][i]);
        return ans;：w
    }
};