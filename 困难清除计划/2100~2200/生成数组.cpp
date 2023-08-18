// https://leetcode.cn/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/



// 暴力dp
class Solution {
public:
    static constexpr int mod = 1000000007;
    int numOfArrays(int n, int m, int k) {
        vector dp(n + 1, vector(k + 1, vector<int>(m + 1)));
        for (int i = 1; i <= m; ++i) dp[1][1][i] = 1;
        for (int i = 2; i <= n; ++i)
            for (int j = 1; j <= k; ++j) {
                for (int u = 1; u <= m; ++u)
                    for (int v = 1; v <= m; ++v) {
                        if (u > v)
                            dp[i][j][u] = (dp[i][j][u] + dp[i - 1][j - 1][v]) % mod; // 会增加一个cost
                        else 
                            dp[i][j][v] = (dp[i - 1][j][v] + dp[i][j][v]) % mod;
                    }
            }
        int ans = 0;
        for (int i = 1; i <= m; ++i) ans = (ans + dp[n][k][i]) % mod;
        return ans;
    }
};