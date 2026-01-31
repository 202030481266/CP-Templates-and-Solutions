class Solution {
    static constexpr int mod = 1e9 + 7;
    int dp[32][2000]; 
public:
    int numRollsToTarget(int n, int k, int target) {
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= target; ++j)
                for (int x = 1; x <= k && j - x >= i - 1; ++x)
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - x]) % mod;
        return dp[n][target];
    }
}; 