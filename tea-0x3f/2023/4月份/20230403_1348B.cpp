// Problem: B. Phoenix and Beauty
// Contest: Codeforces - Codeforces Round 638 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1348/B
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
    int n, k;
    cin >> n >> k;
    vi arr(n);
    vi vis(n + 1);
    int cur = 0;
    vi res;
    for (int& v : arr) {
        cin >> v;
        if (!vis[v]) {
            vis[v] = 1;
            ++cur;
            res.push_back(v);
        }
    }
    if (cur > k) {
        cout << -1 << '\n';
        return;
    }
    cout << n * k << '\n';
    while ((int)res.size() < k) res.push_back(1);
    for (int i = 0; i < n; ++i) {
        for (int v : res) cout << v << ' ';
    }
    cout << '\n';
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