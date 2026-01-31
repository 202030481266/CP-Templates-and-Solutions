// https://codeforces.com/problemset/problem/1748/E
// 使用了笛卡尔树的划分性质（本质上这种划分是基于一种观察，key本质上是区间的划分，而value的堆性质反映了区间的某种属性的最值划分）
// 笛卡尔树 u 节点将u的子树划分为了两个区间，但是这两个区间的最大值都一定不超过 value[u]

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
const int maxn = 200005;
int n, m, a[maxn], st[maxn], ls[maxn], rs[maxn];

void solve() {
    cin >> n >> m;
    int mx = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; // from 1 index
        if (a[i] > a[mx]) mx = i;
    }
    int top = 0; // [0, top)
    memset(ls, 0, sizeof(ls));
    memset(rs, 0, sizeof(rs));
    for (int i = 1; i <= n; ++i) {
        int p = top;
        while (p > 0 && a[st[p-1]] < a[i]) --p;
        if (p > 0) rs[st[p-1]] = i;
        if (p < top) ls[i] = st[p];
        st[p++] = i;
        top = p;
    }
    // dp[u][x]=dp[u][i] * dp[u][j] * (u==x) (i < x and j <= x)
    vector dp(n+1, vector<ll>(m+1));
    auto dfs = [&](int u, auto&& dfs_ref) -> void {
        if (ls[u]) dfs_ref(ls[u], dfs_ref);
        if (rs[u]) dfs_ref(rs[u], dfs_ref);
        if (ls[u] && rs[u]) {
            for (int i = 1; i <= m; ++i) {
                dp[u][i] = (dp[ls[u]][i-1] * dp[rs[u]][i]) % mod;
            }
        }
        else if (ls[u]) {
            for (int i = 1; i <= m; ++i) {
                dp[u][i] = dp[ls[u]][i-1];
            }
        }
        else if (rs[u]) {
            for (int i = 1; i <= m; ++i) {
                dp[u][i] = dp[rs[u]][i];
            }
        }
        else {
            for (int i = 1; i <= m; ++i) {
                dp[u][i] = 1;
            }
        }
        for (int i = 1; i <= m; ++i) {
            dp[u][i] = (dp[u][i] + dp[u][i-1]) % mod;
        }
    };
    dfs(mx, dfs);
    cout << dp[mx][m] << endl;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
