// https://codeforces.com/problemset/problem/1009/F
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e6 + 7;
int n, son[maxn], a[maxn], f[maxn];
int dfn[maxn], tot, len[maxn], dp[maxn], ans[maxn];
vector<int> g[maxn];

void dfs1(int u, int fa) {
    f[u] = fa;
    for (int v : g[u]) {
        if (v != fa) {
            dfs1(v, u);
            if (len[v] > len[son[u]]) son[u] = v;
        }
    }
    len[u] = len[son[u]] + 1;
}
void dfs2(int u) {
    dfn[u] = ++tot;
    if (!son[u]) {
    	dp[dfn[u]] = 1;
    	ans[u] = 0;
    	return;
    }
    dfs2(son[u]);
    dp[dfn[u]] = 1; // dp[u][0] = 1
    ans[u] = ans[son[u]] + 1;
    for (int v : g[u]) {
        if (v != son[u] && v != f[u]) {
            dfs2(v);
            for (int i = 1; i <= len[v]; ++i) {
                dp[dfn[u] + i] += dp[dfn[v] + i - 1];
                if (dp[dfn[u] + i] > dp[dfn[u] + ans[u]] || dp[dfn[u] + i] == dp[dfn[u] + ans[u]] && i < ans[u])
                    ans[u] = i;
            }
        }
    }
    if (dp[ans[u] + dfn[u]] == 1) ans[u] = 0;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }
}