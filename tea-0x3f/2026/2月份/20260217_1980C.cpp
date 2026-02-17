// Problem: C. Sofia and the Lost Operations
// Contest: Codeforces - Codeforces Round 950 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1980/C
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
    int n, m;
    cin >> n;
    vi a(n), b(n);
    for (int& v : a) cin >> v;
    for (int& v : b) cin >> v;
    cin >> m;
    vi d(m), e, f;
    for (int& v : d) cin >> v;
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) e.push_back(b[i]);
        else f.push_back(a[i]);
    }
    bool ed = false;
    for (int v : f) {
        if (v == d[m - 1]) {
            ed = true;
            break;
        }
    }
    bool flag = false;
    for (int v : e) {
        if (v == d[m - 1]) {
            flag = true;
            break;
        }
    }
    if (e.empty()) {
        if (ed) cout << "YES\n";
        else cout << "NO\n";
        return;
    }
    ranges::sort(d);
    ranges::sort(e);
    int p = 0;
    for (int i = 0; i < m && p < e.size(); ++i) {
        if (d[i] == e[p]) ++p;
    }
    if (p < e.size()) {
        cout << "NO\n";
        return;
    }
    if (flag || ed) cout << "YES\n";
    else cout << "NO\n";
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