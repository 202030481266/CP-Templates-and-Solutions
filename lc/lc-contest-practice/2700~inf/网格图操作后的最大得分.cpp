#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int N = 101;
ll dp[2][4][N], sum[N][N], f[2];

// 3000分难度

class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        memset(dp, 0, sizeof(dp));
        memset(sum, 0, sizeof(sum));
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                sum[i][j] = sum[i][j-1] + grid[j-1][i-1];
            }
        }
        int pre = 0, cur = 1;
        for (int i = 2; i <= n; ++i) {
            memset(dp[cur], 0 , sizeof(dp[cur]));
            // update dp[cur][0], x1 < x2 , x1 > 0 and x2 > 0
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= j; ++k) {
                    dp[cur][0][j] = max(dp[cur][0][j], max(dp[pre][0][k], dp[pre][1][k]) + sum[i-1][j]-sum[i-1][k]);
                }
            }
            // update dp[cur][1], x1 = 0, x2 > 0
            for (int j = 1; j <= n; ++j) {
                dp[cur][1][j] = f[pre] + sum[i-1][j];
                for (int k = 1; k <= n; ++k) {
                    if (k >= j)
                        dp[cur][1][j] = max(dp[cur][1][j], dp[pre][3][k]);
                    else
                        dp[cur][1][j] = max(dp[cur][1][j], dp[pre][3][k]-sum[i-1][k]+sum[i-1][j]);
                }
            }
            // update dp[cur][2], x1 > x2, x1 > 0 and x2 > 0
            for (int j = 1; j <= n; ++j) {
                for (int k = j; k <= n; ++k) {
                    dp[cur][2][j] = max(dp[cur][2][j], max({dp[pre][2][k],dp[pre][0][k], dp[pre][1][k]}) + sum[i][k]-sum[i][j]);
                }
            }
            // update dp[cur][3], x1 > 0 , x2 = 0
            for (int j = 1; j <= n; ++j) {
                dp[cur][3][j] = max({dp[pre][0][j], dp[pre][1][j], dp[pre][2][j]}) + sum[i][j];
            }
            // updaet f[cur], x1 = 0, x2 = 0
            f[cur] = f[pre];
            for (int j = 1; j <= n; ++j) {
                f[cur] = max(f[cur], dp[pre][3][j]);
            }
            swap(cur, pre);
        }
        ll ans = f[pre];
        for (int i = 1; i <= n; ++i) ans = max(ans, max({dp[pre][0][i], dp[pre][1][i], dp[pre][2][i], dp[pre][3][i]}));
        return ans;
    }
};