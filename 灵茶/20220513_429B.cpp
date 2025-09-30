#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 1003;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int n, m;
int arr[MAXN][MAXN];
ll dp[4][MAXN][MAXN];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> arr[i][j];
    }
    auto cal = [&](int dx, int dy, int idx) -> void {
        for (int i = dx < 0 ? n : 1; dx < 0 ? i >= 1 : i <= n; i += dx) {
            for (int j = dy < 0 ? m : 1; dy < 0 ? j >= 1 : j <= m; j += dy) {
                dp[idx][i][j] = max(dp[idx][i - dx][j], dp[idx][i][j - dy]) + arr[i][j];
            }
        }
    };
    cal(1, 1, 0);
    cal(-1, -1, 1);
    cal(1, -1, 2);
    cal(-1, 1, 3);
    ll ans = 0;
    for (int i = 2; i < n; ++i) {
        for (int j = 2; j < m; ++j) {
            ans = max(ans, dp[0][i][j - 1] + dp[1][i][j + 1] + dp[2][i - 1][j] + dp[3][i + 1][j]);
            ans = max(ans, dp[0][i - 1][j] + dp[1][i + 1][j] + dp[2][i][j + 1] + dp[3][i][j - 1]);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}