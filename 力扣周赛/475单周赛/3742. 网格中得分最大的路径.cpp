#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int dp[201][201][401];
int f[201][201];
int flag;

void init() {
    if (flag) return;
    flag = 1;
    memset(dp, -1, sizeof(dp));
}

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        init();
        int n = grid.size(), m = grid[0].size();
        if (k >= m + n - 2) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]) + grid[i - 1][j - 1];
                }
            }
            return f[n][m];
        }
        else {
            dp[1][0][0] = dp[0][1][0] = 0;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    for (int x = 0; x <= min(k, i + j - 2); ++x) {
                        dp[i][j][x] = -1;
                        if (grid[i - 1][j - 1]) {
                            if (x > 0) {
                                if (dp[i - 1][j][x - 1] != -1) dp[i][j][x] = max(dp[i][j][x], dp[i - 1][j][x - 1] + grid[i - 1][j - 1]);
                                if (dp[i][j - 1][x - 1] != -1) dp[i][j][x] = max(dp[i][j][x], dp[i][j - 1][x - 1] + grid[i - 1][j - 1]);
                            }
                        }
                        else dp[i][j][x] = max(dp[i - 1][j][x], dp[i][j - 1][x]);
                    }
                }
            }
            int ans = -1;
            for (int i = 0; i <= k; ++i) ans = max(ans, dp[n][m][i]);
            return ans;
        }
    }
};