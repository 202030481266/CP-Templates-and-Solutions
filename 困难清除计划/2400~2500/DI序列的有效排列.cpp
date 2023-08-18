class Solution {
    static constexpr int mod = 1e9 + 7;
    int dp[210][210];
public:
    // dp 难题
    int numPermsDISequence(string s) {
        int n = s.size();
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == 'D') {
                for (int j = 0; j <= i; ++j) {
                    for (int k = j + 1; k <= i; ++k)
                        dp[i][j] = (dp[i][j] + dp[i - 1][k - 1]) % mod;
                }
            }
            else {
                for (int j = 0; j <= i; ++j) {
                    for (int k = j - 1; k >= 0; --k) 
                        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= n; ++i) ans = (ans + dp[n][i]) % mod;
        return ans;
    }
};