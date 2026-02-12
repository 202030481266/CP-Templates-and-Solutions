// Problem: F. Copy or Prefix Sum
// Contest: Codeforces - Codeforces Round 701 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1485/F
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

// dp[i][s] = dp[i - 1][s - b[i]] if s != b[i]
// dp[i][b[i]] = sum of dp[i - 1][s]
void solve() {
    int n;
    cin >> n;
    vl arr(n + 1); 
    vl sum(n + 1);
    vector<pair<ll, int>> b;
    b.emplace_back(0, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        sum[i] = sum[i - 1] + arr[i];
        b.emplace_back(sum[i], i);
    }
    ranges::sort(b);
    int cur = 0;
    vi rk(n + 1);
    for (int i = 0; i < (int)b.size(); ++i) {
        if (i == 0 || b[i].first != b[i - 1].first) ++cur;
        rk[b[i].second] = cur;
    }
    vl dp(n + 1);
    vl f(cur + 1);
    ll tot = 1;
    f[rk[0]] = dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = (tot - f[rk[i - 1]]) % MOD;
        tot = (tot + dp[i]) % MOD;
        f[rk[i - 1]] = (f[rk[i - 1]] + dp[i]) % MOD;
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) { 
    	ans = (ans + dp[i]) % MOD;
    }
    cout << (ans + MOD) % MOD << '\n';
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