// Problem: B. Greg and Graph
// Contest: Codeforces - Codeforces Round 179 (Div. 1)
// URL: https://codeforces.com/problemset/problem/295/B
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
    vll dp(n + 1, vl(n + 1, INF));
    vii vis(n + 1, vi(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) cin >> dp[i][j];
    }
    vi perm(n + 1);
    for (int i = 1; i <= n; ++i) cin >> perm[i];
    ll sum = 0;
    vl ans;
    vi use(n + 1);
    for (int i = 1; i <= n; ++i) dp[i][i] = 0;
    for (int i = n; i >= 1; --i) {
        int k = perm[i];
        use[k] = 1;
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (use[u] && use[v]) {
                    if (vis[u][v]) sum -= dp[u][v];
                }
                if (dp[u][k] + dp[k][v] < dp[u][v]) {
                    dp[u][v] = dp[u][k] + dp[k][v];
                    
                }
                if (use[u] && use[v]) {
                    vis[u][v] = 1;
                    sum += dp[u][v];
                }
            }
        }
        ans.push_back(sum);
    }
    for (int i = n - 1; i >= 0; --i) cout << ans[i] << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}