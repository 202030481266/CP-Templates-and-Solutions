// Problem: A. Hilbert's Hotel
// Contest: Codeforces - Codeforces Round 639 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1344/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    vi cnt(n);
    for (int i = 0; i < n; ++i) {
        int x = ((i + arr[i]) % n + n) % n;
        if (cnt[x]) {
            cout << "NO\n";
            return;
        }
        cnt[x] = 1;
    }
    cout << "YES\n";
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