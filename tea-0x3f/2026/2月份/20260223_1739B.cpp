// Problem: B. Array Recovery
// Contest: Codeforces - Educational Codeforces Round 136 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1739/B
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
    // must contain a solutions that di = sum(aj) for i 0<=j<=i
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    int sum = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] && arr[i] <= sum) {
            cout << -1 << '\n';
            return;
        }
        sum += arr[i];
    }
    sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
        cout << sum << ' ';
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