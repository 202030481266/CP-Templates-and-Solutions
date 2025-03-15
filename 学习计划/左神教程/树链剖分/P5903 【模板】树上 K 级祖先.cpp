#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

#define ui unsigned int
ui s;
inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}
const int maxn = 5e5 + 7;
int n, q, root, dep[maxn], f[maxn][20], top[maxn], dfn[maxn];
int down[maxn], up[maxn], son[maxn], len[maxn], tot, high[maxn];
vector<int> g[maxn];

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; i < 20; ++i) f[u][i] = f[f[u][i-1]][i-1];
    for (int v : g[u]) {
        if (v != fa) {
            dfs1(v, u);
            if (len[v] > len[son[u]]) son[u] = v;
        }
    }
    len[u] = len[son[u]] + 1;
}
void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++tot;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int v : g[u]) {
        if (v != son[u] && v != f[u][0]) dfs2(v, v);
    }
}
int solve(int x, int k) {
    if (k == 0) return x;
    int h = high[k];
    if ((1<<h) == k) return f[x][h];
    x = f[x][h];
    k -= (1<<h) + (dep[x] - dep[top[x]]);
    x = top[x];
    return k >= 0 ? up[dfn[x] + k] : down[dfn[x] - k];
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q >> s;
    for (int i = 1, fa; i <= n; ++i) {
        cin >> fa;
        g[fa].push_back(i);
        g[i].push_back(fa);
        if (fa == 0) root = i;
    }
    dfs1(root, 0);
    dfs2(root, root);
    for (int i = 1; i <= n; ++i) {
        if (top[i] == i) {
            for (int j = 0, x = i, y = i; j < len[i]; x = son[x], y = f[y][0], ++j) {
                up[dfn[i] + j] = y;
                down[dfn[i] + j] = x;
            }
        }
    }
    high[0] = -1;
    for (int i = 1; i <= n; ++i) high[i] = high[i/2] + 1;
    ll ans = 0, res = 0;
    for (int i = 1, x, k; i <= q; ++i) {
        x = (get(s) ^ ans) % n + 1;
        k = (get(s) ^ ans) % dep[x];
        ans = solve(x, k);
        res ^= i * ans;
    }
    cout << res << '\n';
}