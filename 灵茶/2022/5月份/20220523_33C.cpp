#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vector<int> sum(n + 2);
    vector mn(n + 1, INF);
    for (int i = 1; i <= n; ++i) cin >> sum[i];
    mn[n] = sum[n];
    for (int i = n - 1; i >= 1; --i) {
        sum[i] += sum[i + 1];
        mn[i] = min(mn[i + 1], sum[i]);
    }
    int ans = max(- 2 * mn[1], 0), cur = INF;
    for (int i = 1; i <= n; ++i) {
        cur = min(cur, sum[1] - sum[i + 1]);
        if (i < n) ans = max(ans, max(0, -2 * cur) + max(- 2 * mn[i + 1], 0));
        else ans = max(ans, -2 * cur);
    }
    cout << ans + sum[1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}