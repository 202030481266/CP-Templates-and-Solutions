#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int dp[81][81], dfn[81][81];

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<pii> arr; 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                arr.emplace_back(i, j);
                dp[i][j] = inf;
            }
        }
        ranges::sort(arr, [&](const auto& x, const auto& y){
            return grid[x.first][x.second] > grid[y.first][y.second];
        });
        for (int i = 0; i < n * m; ++i) dfn[arr[i].first][arr[i].second] = i;
        vector<int> mn(n * m, inf);
        dp[0][0] = 0;
        int ans = inf;
        for (int x = 0, p; x <= k; ++x) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (i - 1 >= 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + grid[i][j]);
                    if (j - 1 >= 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + grid[i][j]);
                    if (x > 0) dp[i][j] = min(dp[i][j], mn[dfn[i][j]]);
                }
            }
            ans = min(ans, dp[n-1][m-1]);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    mn[dfn[i][j]] = dp[i][j];
                }
            }
            p = 0;
            while (p < n * m) {
                int i = p + 1;
                while (i < n * m && grid[arr[i].first][arr[i].second] == grid[arr[p].first][arr[p].second]) ++i;
                for (int j = p; j < i; ++j) {
                    if (j > 0) mn[j] = min(mn[j], mn[j-1]);
                }
                for (int j = p; j < i; ++j) mn[j] = mn[i-1];
                p = i;
            }
        }
        return ans;
    }
};
