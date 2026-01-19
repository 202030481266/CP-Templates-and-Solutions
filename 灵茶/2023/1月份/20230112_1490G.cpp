#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    // k * s + p[i] >= x
    int n, m;
    cin >> n >> m;
    vi arr(n + 1);
    vector<ll> sum(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    ll mx = -LLINF;
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + arr[i];
        mx = max(mx, sum[i]);
    }
    vector<ll> ans(m);
    vector<pii> qs;
    for (int q = 0; q < m; ++q) {
        int x;
        cin >> x;
        if (x > mx) {
            if (sum[n] <= 0) {
                ans[q] = -1;
                continue;
            }
            int k = (x - mx + sum[n] - 1) / sum[n];
            ans[q] += 1LL * k * n;
            x -= k * sum[n];
        }
        qs.emplace_back(x, q);
    }
    ranges::sort(qs);
    int p = 0;
    for (int i = 1; i <= n; ++i) {
        while (p < qs.size() && sum[i] >= qs[p].first) {
            ans[qs[p].second] += i;
            ++p;
        }
    }
    for (int i = 0; i < m; ++i) {
        ll res = ans[i] == -1 ? ans[i] : ans[i] - 1;
        cout << res << ' ';
    }
    cout << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
