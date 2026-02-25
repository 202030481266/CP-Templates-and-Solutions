// Problem: C. Serval and The Formula
// Contest: Codeforces - Codeforces Round 1011 (Div. 2)
// URL: https://codeforces.com/problemset/problem/2085/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
    ll x, y;
    cin >> x >> y;
    // a + b = (a ^ b) + 2 * (a & b)    
    // (x + k) & (y + k) == 0
    if ((x & y) == 0) {
        cout << 0 << '\n';
        return;
    }
    if (x == y) {
        cout << -1 << '\n';
        return;
    }
    if (x < y) swap(x, y);
    int w = bit_width(1ull * x);
    ll ans = (1ll << w) - x;
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