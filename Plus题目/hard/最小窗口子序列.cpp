class Solution {
public:
    string minWindow(string s1, string s2) {
        int n = s1.size(), m = s2.size(), dp[n + 1][m + 1];
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i <= n; ++i)
            dp[i][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = dp[i - 1][j] + 1; // not use s1[i]
                if (s1[i - 1] == s2[j - 1]) { // use s1[i]
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
                }
            }
        }
        int ans = 0x3f3f3f3f, ed = -1;
        for (int i = 1; i <= n; ++i) {
            if (dp[i][m] < ans) {
                ans = dp[i][m];
                ed = i;
            }
        }
        return ed == -1 ? "" : s1.substr(ed - ans, ans);
    }
};