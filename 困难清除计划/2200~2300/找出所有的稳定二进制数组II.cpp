#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        int n = zero + one,dp[2][zero+1][one+1],f[one+1][zero+1],g[zero+1][one+1];
        memset(dp,0,sizeof(dp));
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        // dp
        for (int i = 0; i <= zero; i++) {
            for (int j = 0; j <= one; ++j) {
                if (i == 0 && j == 0)
                    dp[0][i][j] = dp[1][i][j] = 1;
                if (i > 0) // can end with 0
                    dp[0][i][j] = (f[j][i-1]-(i > limit ? f[j][i-limit-1] : 0)+mod) % mod;
                if (j > 0) // can end with 1
                    dp[1][i][j] = (g[i][j-1]-(j > limit ? g[i][j-limit-1] : 0)+mod) % mod;
                // 更新f,g
                // f[i][j] = f[i][j-1]+dp[1][j][i],1的数量是i,0的数量是j
                // g[i][j] = g[i][j-1]+dp[0][i][j],1的数量是j,0的数量是i
                f[j][i] = ((i == 0 ? 0 : f[j][i-1]) + dp[1][i][j]) % mod;
                g[i][j] = ((j == 0 ? 0 : g[i][j-1]) + dp[0][i][j]) % mod;
            }
        }
        return (dp[0][zero][one]+dp[1][zero][one]) % mod;
    }
};