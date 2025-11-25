#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int MAXN = 5003;

int n, m, k, arr[MAXN];
ll sum[MAXN], dp[MAXN][MAXN];

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + arr[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) dp[i][j] = dp[i - 1][j];
        for (int j = 1; j <= k && j * m <= i; ++j) {
            dp[i][j] = max(dp[i][j], dp[i - m][j - 1] + sum[i] - sum[i - m]);
        }
    }
    cout << dp[n][k] << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    solve();
}