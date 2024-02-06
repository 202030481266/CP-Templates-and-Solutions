class Solution {
public:
    int maxA(int n) {
        // 个人觉得此题不止中等难度

        int dp[60];
        memset(dp, 0, sizeof(dp));
        
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;
            for (int x = i - 3; x >= 1; --x) {
                dp[i] = max(dp[i], dp[x] * (i - x - 1));
            }
        }

        return dp[n];
    }
};