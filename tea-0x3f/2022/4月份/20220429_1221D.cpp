#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300005;
static constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
ll dp[MAXN][3], a[MAXN], b[MAXN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i][1] = dp[i][2] = INF;
    }
    dp[1][0] = 0;
    dp[1][1] = b[1];
    dp[1][2] = b[1] * 2;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (a[i] + j != a[i - 1] + k && dp[i - 1][k] < INF) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + j * b[i]);
                }
            }
        }
    }
    ll ans = INF;
    for (int i = 0; i < 3; ++i) ans = min(ans, dp[n][i]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}