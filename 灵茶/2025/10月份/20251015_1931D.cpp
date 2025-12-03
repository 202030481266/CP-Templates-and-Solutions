#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int arr[MAXN];

void solve() {
    static constexpr int offset = 1e9;
    int n, x, y;
    unordered_map<ll, ll> cnt;
    cin >> n >> x >> y;
    cnt.reserve(n * 10);
    ll ans = 0;
    for (int i = 0, val; i < n; ++i) {
        cin >> val;
        int rx = val % x, ry = val % y, tmp = (x - rx + x) % x;
        ll key = 1ll * tmp * offset + ry;
        if (cnt.contains(key)) ans += cnt[key];
        ++cnt[1ll * rx * offset + ry];
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
