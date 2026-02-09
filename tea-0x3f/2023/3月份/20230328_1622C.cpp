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
    int n;
    ll k;
    cin >> n >> k;
    vl arr(n);
    ll sum = 0;
    for (ll& v : arr) {
        cin >> v;
        sum += v;
    }
    if (sum <= k) {
        cout << 0 << '\n';
        return;
    }
    k = sum - k;
    ranges::sort(arr);
    ll ans = k; // only 1 type operation
    for (int i = n - 1; i > 0; --i) {
        k -= arr[i] - arr[0];
        if (k < 0) {
            ans = min(ans, 1ll * (n - i));
            break;
        }
        ll x = (k + n - i) / (n - i + 1);
        ans = min(ans, x + n - i);
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