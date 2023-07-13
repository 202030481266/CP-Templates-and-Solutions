class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int dp[n][m];
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < m; ++i) dp[0][i] = matrix[0][i];
        for (int i = 1; i < n; ++i) 
            for (int j = 0; j < m; ++j) {
                if (i - 1 >= 0) {
                    dp[i][j] = dp[i - 1][j];
                    if (j - 1 >= 0) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                    if (j + 1 < m) dp[i][j] = min(dp[i][j], dp[i - 1][j + 1]); 
                }
                dp[i][j] += matrix[i][j];
            }
        return *min_element(dp[n - 1], dp[n - 1] + m);
    }
};