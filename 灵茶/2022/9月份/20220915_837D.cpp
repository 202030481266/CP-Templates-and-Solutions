// Problem: D. Round Subset
// Contest: Codeforces - Educational Codeforces Round 26
// URL: https://codeforces.com/problemset/problem/837/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, k; 
ll arr[300];
int a[300], b[300];
int dp[3602][203][2];

void solve() {
    cin >> n >> k;    
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    int sa = 0, sb = 0;
    for (int i = 1; i <= n; ++i) {
        ll x = arr[i];
        while (x % 2 == 0) {
            ++a[i];
            x /= 2;
        }
        x = arr[i];
        while (x % 5 == 0) {
            ++b[i];
            x /= 5;
        }
        sa += a[i];
        sb += b[i];
    }
    int N = min(sa, sb);
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = dp[0][0][1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int x = N - min(a[i], b[i]); x >= 0; --x) {
            for (int j = k - 1; j >= 0; --j) {
                int tmp = dp[x][j][0];
                if (tmp != -1) {
                    if (tmp + a[i] >= x + b[i]) {
                        if (x + b[i] <= N)
                            dp[x + b[i]][j + 1][0] = max(dp[x + b[i]][j + 1][0], tmp + a[i]);
                    }
                    else {
                        if (tmp + a[i] <= N)
                            dp[tmp + a[i]][j + 1][1] = max(dp[tmp + a[i]][j + 1][1], x + b[i]);
                    }
                }
                tmp = dp[x][j][1];
                if (tmp != -1) {
                    if (tmp + b[i] >= x + a[i]) {
                        if (x + a[i] <= N)
                            dp[x + a[i]][j + 1][1] = max(dp[x + a[i]][j + 1][1], tmp + b[i]);
                    }
                    else {
                        if (tmp + b[i] <= N) 
                            dp[tmp + b[i]][j + 1][0] = max(dp[tmp + b[i]][j + 1][0], x + a[i]);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (dp[i][k][0] != -1 || dp[i][k][1] != -1) ans = i;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}