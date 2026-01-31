#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr ll inf = 1e18;

class Solution {
public:
    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        vector dp(m, vector<ll>(n, inf));       
        dp[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 >= 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + waitCost[i][j] + (i + 1) * (j + 1));
                if (j - 1 >= 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + waitCost[i][j] + (i + 1) * (j + 1));
            }
        }
        return dp[m-1][n-1] - waitCost[m-1][n-1];
    }
};