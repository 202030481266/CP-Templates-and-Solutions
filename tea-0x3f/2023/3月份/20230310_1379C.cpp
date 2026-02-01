#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    int n, m;
    cin >> m >> n;
    vi a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    vector<tuple<int, int, int>> arr;
    for (int i = 0; i < n; ++i) {
        arr.emplace_back(a[i], 0, i);
        arr.emplace_back(b[i], 1, i);
    }
    ranges::sort(arr);
    ll ans = 0;
    ll cur = 0;
    vi activate(n);
    for (int i = (int)arr.size() - 1; i >= 0 && m > 0; --i) {
        auto [val, t, idx] = arr[i];
        if (!t) {
            cur += val;
            --m;
            ans = max(ans, cur);
            activate[idx] = 1;
        }
        else {
            if (activate[idx]) {
                ans = max(ans, cur + 1ll * val * m);
                break;
            }
            ans = max(ans, cur + 1ll * val * (m - 1) + a[idx]);
        }
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
