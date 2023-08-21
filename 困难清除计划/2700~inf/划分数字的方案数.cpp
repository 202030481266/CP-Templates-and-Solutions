class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int numberOfCombinations(string num) {
        int n = num.size(), dp[n + 1][n + 1], lcp[n + 1][n + 1];
        memset(dp, 0, sizeof(dp));
        memset(lcp, 0, sizeof(lcp));
        if (num[0] == '0') return 0; //小特判
        // 优化字符串判断
        // 有两种思路： 后缀数组或者动态规划，由于数据量很小使用LCP
        for (int i = n - 1; i >= 0; --i)
            for (int j = n - 1; j >= 0; --j) 
                if (num[i] == num[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
        dp[0][0] = dp[0][1] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                if (num[i - j] != '0') {
                    // for (int k = 0; k < j && k <= i - j; ++k) dp[i][j] = (dp[i][j] + dp[i - j][k]) % mod;
                    dp[i][j] = (dp[i][j] + dp[i - j][min(j - 1, i - j)]) % mod;
                    if (i - j < j) continue;
                    int len = lcp[i - j][i - j * 2];
                    if ((len >= j || (num[i - j + len] > num[i - j * 2 + len])))
                        dp[i][j] = (dp[i][j] + dp[i - j][j] - dp[i - j][j - 1] + mod) % mod;
                }
            }
            for (int j = 1; j <= i; ++j) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
        }
        return dp[n][n]; 
    }
};