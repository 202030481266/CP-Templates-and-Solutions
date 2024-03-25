class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // dp[i][j] = sum{ dp[i - 1][j - k * coins[i]] }
        // 同余划分
        int n = coins.size(), pre = 0;
        int dp[amount + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < coins[i] && coins[i] <= amount; ++j) {
                int sum = dp[j];
                for (int k = j + coins[i]; k <= amount; k += coins[i]) {
                    pre = dp[k];
                    dp[k] += sum;
                    sum += pre;
                }
            }
        }
        return dp[amount];
    }
};