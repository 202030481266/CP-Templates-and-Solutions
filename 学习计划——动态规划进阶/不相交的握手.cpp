class Solution {
    static constexpr int mod = 1e9 + 7;
    using ll = long long;
public:
    int numberOfWays(int numPeople) {
        ll dp[1001];
        memset(dp, 0, sizeof(dp));

        dp[0] = dp[2] = 1;
        for (int i = 4; i <= numPeople; i += 2) {
            for (int j = 0; j < (i - 2) / 2; j += 2) {
                dp[i] = (dp[i] + 2 * dp[j] * dp[i - 2 - j]) % mod;
            }
            dp[i] = (dp[i] + dp[(i - 2) / 2] * dp[(i - 2) / 2]) % mod;
        }
        return dp[numPeople];
    }
};