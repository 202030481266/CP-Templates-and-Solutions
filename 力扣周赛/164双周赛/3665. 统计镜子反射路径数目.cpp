#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int dp[501][501][2];

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) dp[i][j][0] = dp[i][j][1] = 0;
        }
        dp[0][0][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!grid[i][j]) {
                    if (i - 1 >= 0) dp[i][j][0] = (dp[i-1][j][0] + dp[i][j][0]) % mod;
                    if (j - 1 >= 0) {
                        if (grid[i][j-1]) dp[i][j][0] = (dp[i][j][0] + dp[i][j-1][1]) % mod;
                        else dp[i][j][0] = (dp[i][j][0] + dp[i][j-1][0]) % mod;
                    }
                }
                else {
                    if (i - 1 >= 0) dp[i][j][1] = (dp[i][j][1] + dp[i-1][j][0]) % mod;
                    if (j - 1 >= 0) {
                        if (grid[i][j-1]) dp[i][j][0] = (dp[i][j][0] + dp[i][j-1][1]) % mod;
                        else dp[i][j][0] = (dp[i][j][0] + dp[i][j-1][0]) % mod;
                    }
                }
            }
        }
        return dp[n-1][m-1][0];
    }
};
