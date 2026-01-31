class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.size(), dp[n][n];
        memset(dp, 0x3f, sizeof(dp));

        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (len == 1) dp[i][j] = 0;
                else if (len == 2) dp[i][j] = (s[i] == s[j] ? 0 : 1);
                else {
                    if (s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1];
                    dp[i][j] = min(dp[i][j], min(dp[i + 1][j], dp[i][j - 1]) + 1);
                }
            }
        }
        return dp[0][n - 1] <= k;
    }
};