// Problem: D. Buying Jewels
// Contest: Codeforces - Codeforces Global Round 25
// URL: https://codeforces.com/problemset/problem/1951/D
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
    ll n, k;
    cin >> n >> k;
    if (n < k) {
        cout << "NO\n";
        return;
    }
    if (2 * k <= n) {
        cout << "YES\n" << 2 << '\n' << (n - k + 1) << ' ' << 1 << '\n';
        return;
    }
    if (n == k) {
        cout << "YES\n" << 1 << '\n' << 1 << '\n';
        return;
    }
    if ((n & 1) && (k == n / 2 + 1)) {
        cout << "YES\n" << 2 << '\n' << 2 << ' ' << 1 << '\n';
        return;
    }
    cout << "NO\n";
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