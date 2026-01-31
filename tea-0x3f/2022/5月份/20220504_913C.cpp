#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, L;
    cin >> n >> L;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    b[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; --i) b[i] = min(b[i + 1], a[i]);
    vector<ll> dp(31, 1e18);
    dp[0] = b[0];
    for (int i = 1; i < 31; ++i) {
        if (i < n) dp[i] = b[i];
        dp[i] = min(dp[i], 2 * dp[i - 1]);
    }
    int w = bit_width(1u * L);
    ll ans = 1e18, cur = 0;
    for (int i = w - 1; i >= 0; --i) {
        if (i + 1 < 31) ans = min(ans, cur + dp[i + 1]);
        if (L >> i & 1) cur += dp[i];
    }
    ans = min(ans, cur);
    cout << ans << '\n';
}