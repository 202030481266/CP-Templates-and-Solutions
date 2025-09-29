#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int n, m;

void solve() {
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (ll& v : a) cin >> v;
    for (ll& v : b) cin >> v;
    ranges::sort(a);
    ranges::sort(b);
    vector<ll> sa(n), sb(m);
    sa[0] = a[0];
    sb[m - 1] = b[m - 1];
    for (int i = 1; i < n; ++i) sa[i] = sa[i - 1] + a[i];
    for (int i = m - 2; i >= 0; --i) sb[i] = sb[i + 1] + b[i];
    ll ans, cost;
    int i = 0, j = 0;
    while (j < m && b[j] <= a[i]) ++j;
    cost = (i + 1) * a[i] - sa[i];
    if (j < m) cost += sb[j] - (m - j) * a[i];
    ans = cost;
    while (i + 1 < n || j + 1 < m) {
        if (j + 1 < m && i + 1 < n) {
            if (a[i + 1] > b[j + 1]) {
                ++j;
                ans = min(ans, (i + 1) * b[j] - sa[i] + sb[j] - (m - j) * b[j]);
            }
            else {
                ++i;
                while (j < m && b[j] <= a[i]) ++j;
                cost = (i + 1) * a[i] - sa[i];
                if (j < m) cost += sb[j] - (m - j) * a[i];
                ans = min(ans, cost);
            }
        }
        else if (j + 1 < m) {
            ++j;
            ans = min(ans, (i + 1) * b[j] - sa[i] + sb[j] - (m - j) * b[j]);
        }
        else if (i + 1 < n) {
            ++i;
            while (j < m && b[j] <= a[i]) ++j;
            cost = (i + 1) * a[i] - sa[i];
            if (j < m) cost += sb[j] - (m - j) * a[i];
            ans = min(ans, cost);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}