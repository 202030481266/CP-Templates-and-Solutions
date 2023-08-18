class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int numberOfUniqueGoodSubsequences(string binary) {
        int n = binary.size(), dp[n][2];
        memset(dp, 0, sizeof(dp));
        dp[0][1] = (binary[0] == '1');
        for (int i = 1; i < n; ++i) {
            dp[i][1] = dp[i - 1][1];
            dp[i][0] = dp[i - 1][0];
            if (binary[i] == '1') {
                dp[i][1] = (dp[i][1] + dp[i - 1][0] + 1) % mod;
            }
            else {
                dp[i][0] = (dp[i][0] + dp[i - 1][1]) % mod;
            }
        }
        int ans = (dp[n - 1][0] + dp[n - 1][1]) % mod;
        for (int i = 0; i < n; ++i)
            if (binary[i] == '0') 
                return (ans + 1) % mod;
        return ans;
    }
};