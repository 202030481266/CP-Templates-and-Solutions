#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 200003;

int n, c, a[MAXN], b[MAXN];

void solve() {
    cin >> n >> c;
    for (int i = 1; i < n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) cin >> b[i];
    cout << 0 << ' ';
    int dp[2], f[2];
    dp[0] = 0;
    dp[1] = c;
    for (int i = 2; i <= n; ++i) {
        f[0] = min(dp[0] + a[i - 1], dp[1] + b[i - 1]);
        f[1] = min(dp[1] + b[i - 1], min(dp[0] + c + b[i - 1], dp[0] + a[i - 1] + c));
        dp[0] = f[0];
        dp[1] = f[1];
        cout << f[0] << ' ';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
}
