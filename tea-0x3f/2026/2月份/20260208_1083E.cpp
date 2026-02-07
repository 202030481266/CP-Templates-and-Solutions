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
    cin >> n;
    vector<tuple<int, int, ll>> arr(n);
    for (auto& [x, y, z] : arr) cin >> x >> y >> z;
    ranges::sort(arr);
    // dp[i]=dp[j]+(ai-aj)*bi-ci
    // dp[i]+ci-ai*bi+aj*bi=dp[j]
    // maintain a upper convex hull, point is (aj,dp[j])
    vi a{0}, b{0};
    vl c{0};
    for (auto [x, y, z] : arr) {
        a.push_back(x);
        b.push_back(y);
        c.push_back(z);
    }
    vl dp(n + 1);
    vi q(n + 3);
    int ql = 0, qr = 0;
    q[qr++] = 0; // (0, dp[0]);
    for (int i = 1; i <= n; ++i) {
        int cur_slope = b[i];
        while (qr - ql >= 2) {
            ll dy = dp[q[ql + 1]] - dp[q[ql]];
            ll dx = a[q[ql + 1]] - a[q[ql]];
            if ((__int128)dy >= (__int128)dx * cur_slope) ++ql;
            else break;
        }
        dp[i] = dp[q[ql]] + 1ll * (a[i] - a[q[ql]]) * b[i] - c[i];
        while (qr - ql >= 2) {
            int p1 = q[qr - 2];
            int p2 = q[qr - 1];
            int p3 = i;
            ll y2_y1 = dp[p2] - dp[p1];
            ll x2_x1 = a[p2] - a[p1];
            ll y3_y2 = dp[p3] - dp[p2];
            ll x3_x2 = a[p3] - a[p2];
            if ((__int128)x2_x1 * y3_y2 >= (__int128)x3_x2 * y2_y1) --qr;
            else break;
        }
        q[qr++] = i;
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
