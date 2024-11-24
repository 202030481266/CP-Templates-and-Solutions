#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 显然这两个点运动是可以完全隔离计算的
int dp[1010][1010];

class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& g) {
        int ans = 0, n = g.size();
        
        for (int i = 0; i < n; ++i) {
            ans += g[i][i];
            g[i][i] = 0;
        }

        // 首先计算(n-1,0)出发的最大路径值
        int m = n/2;
        memset(dp, -0x3f, sizeof(dp));
        dp[n-1][0] = g[n-1][0];
        for (int col = 1; col < n; ++col) {
            int len = (col < m ? col+1 : n-col);
            for (int i = 1; i <= len; ++i) {
                int row = (n-1)-i+1;
                if (col-1 >= 0 && dp[row][col-1] != -inf) 
                    dp[row][col] = max(dp[row][col], dp[row][col-1]);
                if (col-1 >= 0 && row-1 >= 0 && dp[row-1][col-1] != -inf)
                    dp[row][col] = max(dp[row][col], dp[row-1][col-1]);
                if (col-1 >= 0 && row+1 < n && dp[row+1][col-1] != -inf)
                    dp[row][col] = max(dp[row][col], dp[row+1][col-1]);
                if (dp[row][col] != -inf) dp[row][col] += g[row][col];
            }
        }
        ans += dp[n-1][n-1];
        
        // 计算(0,n-1)出发的最大路径值
        memset(dp, -0x3f, sizeof(dp));
        dp[0][n-1] = g[0][n-1];
        for (int row = 1; row < n; ++row) {
            int len = (row < m ? row + 1 : n - row);
            for (int i = 1; i <= len; ++i) {
                int col = (n-1)-i+1;
                if (row-1 >= 0 && dp[row-1][col] != -inf)
                    dp[row][col] = max(dp[row][col], dp[row-1][col]);
                if (row-1 >= 0 && col-1 >= 0 && dp[row-1][col-1] != -inf)
                    dp[row][col] = max(dp[row][col], dp[row-1][col-1]);
                if (row-1 >= 0 && col+1 < n && dp[row-1][col+1] != -inf)
                    dp[row][col] = max(dp[row][col], dp[row-1][col+1]);
                if (dp[row][col] != -inf) dp[row][col] += g[row][col];
            }
        }
        ans += dp[n-1][n-1];
        return ans;
    }
};