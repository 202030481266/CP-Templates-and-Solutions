// Problem: A. Writing Code
// Contest: Codeforces - Codeforces Round 302 (Div. 1)
// URL: https://codeforces.com/problemset/problem/543/A
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, m, b, mod, a[510], dp[510][510], f[510][510];

void solve() {
    cin >> n >> m >> b >> mod;    
    for (int i = 1; i <= n; ++i) cin >> a[i]; 
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= b; ++k) {
                f[j][k] = dp[j][k];
                if (j > 0 && k >= a[i]) f[j][k] = (f[j][k] + f[j - 1][k - a[i]]) % mod;
            }
        }
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= b; ++k) dp[j][k] = f[j][k];
        }
    }
    int ans = 0;
    for (int i = 0; i <= b; ++i) ans = (ans + dp[m][i]) % mod;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}