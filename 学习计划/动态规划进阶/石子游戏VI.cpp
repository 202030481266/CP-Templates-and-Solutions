class Solution {
public:
    bool winnerSquareGame(int n) {
        int dp[n + 1];
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i <= n; ++i) {
            if (dp[i] != -1) continue;
            dp[i] = 0;
            for (int j = 1; i + j * j <= n; ++j) {
                dp[i + j * j] = 1;
            }
        }

        return dp[n];
    }
};