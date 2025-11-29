#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100003;

int n, k, arr[MAXN];
int f[1 << 18], g[1 << 18];

void solve() {
    // sos dp
    cin >> n >> k;
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        mx |= arr[i];
    }
    if (mx == 0) {
        cout << 1ll * n * (n - 1) << '\n';
        return;
    }
    int w = bit_width(1u * mx);
    memset(g, 0, (1 << w) * sizeof(int));
    memset(f, 0, (1 << w) * sizeof(int));
    auto update = [&](int status, int val) -> void {
        if (val > f[status]) {
            g[status] = f[status];
            f[status] = val;
        }
        else if (val > g[status] && val != f[status]) g[status] = val;
    };
    for (int i = 1; i <= n; ++i) update(arr[i], i);
    for (int i = 0; i < w; ++i) {
        for (int j = 1; j < 1 << w; ++j) {
            if (j >> i & 1) {
                update(j, g[j ^ 1 << i]);
                update(j, f[j ^ 1 << i]);
            }
        }
    }
    ll ans = -1e12;
    for (int i = 0; i < 1 << w; ++i) {
        if (g[i] && f[i]) ans = max(ans, 1ll * f[i] * g[i] - 1ll * k * i);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
