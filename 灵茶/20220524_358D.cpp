#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vi a(n), b(n), c(n);
    for (int& v : a) cin >> v;
    for (int& v : b) cin >> v;
    for (int& v : c) cin >> v;
    if (n == 1) {
        cout << a[0] << '\n';
        return;
    }
    vii dp(n, vi(4));
    // b right, b left, a, c
    dp[0][0] = b[0];
    dp[0][2] = a[0];
    dp[0][1] = -INF;
    dp[0][3] = -INF;
    for (int i = 1; i < n; ++i) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][3]) + b[i]; // b b, c b
        dp[i][1] = max(dp[i - 1][2], dp[i - 1][1]) + b[i]; // b b, a b
        dp[i][2] = max(dp[i - 1][0], dp[i - 1][3]) + a[i];
        dp[i][3] = max(dp[i - 1][2], dp[i - 1][1]) + c[i];
    }
    cout << max(dp[n - 1][2], dp[n - 1][1]) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}