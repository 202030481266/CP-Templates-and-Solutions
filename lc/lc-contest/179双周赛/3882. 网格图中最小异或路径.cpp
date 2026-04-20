#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector dp(n, vii(m, vi(1024)));
        dp[0][0][grid[0][0]] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int v = 0; v < 1024; ++v) {
                    if (i - 1 >= 0) dp[i][j][v] |= dp[i - 1][j][v ^ grid[i][j]];
                    if (j - 1 >= 0) dp[i][j][v] |= dp[i][j - 1][v ^ grid[i][j]];
                }
            }
        }
        for (int i = 0; i < 1024; ++i) {
            if (dp[n - 1][m - 1][i]) return i;
        }
        return -1;
    }
};