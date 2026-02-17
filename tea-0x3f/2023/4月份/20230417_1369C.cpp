#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n), b(k);
    for (int& v : a) cin >> v;
    for (int& v : b) cin >> v;
    ranges::sort(a);
    ranges::sort(b);
    ll ans = 0;
    int i = 0, m = n - k;
    for (int j = (int)b.size() - 1; j >= 0; --j, ++m) {
        if (b[j] > 1) {
            ans += a[i] + a[m];
            i += b[j] - 1;
        }
        else ans += 2 * a[m];
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}