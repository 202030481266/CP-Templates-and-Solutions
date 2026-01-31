// https://codeforces.com/problemset/problem/1706/E

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 1e5 + 7;
const int N = maxn << 1;

int n, m, q, T;
int dep[N], fa[N], val[N], up[N][20], cnt = 0;
int dfn[N], ids[N], tot = 0, mn[maxn][20], mx[maxn][20];
vector<int> g[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void dfs (int u, int father) {
    dep[u] = dep[father] + 1;
    up[u][0] = father;
    if (u <= n) {
        dfn[u] = ++tot;
        ids[tot] = u;
    }
    for (int i = 1; i < 20; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v : g[u]) {
        dfs(v, u);
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if (dep[up[x][i]] >= dep[y]) x = up[x][i];
    }   
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (up[x][i] != up[y][i]) {
            x = up[x][i];
            y = up[y][i];
        }
    }
    return up[x][0];
}
void init(int sz) {
    cnt = tot = 0;
    memset(dep, 0, sizeof(int) * (sz + 1));
    memset(fa, 0, sizeof(int) * (sz + 1));
    memset(val, 0, sizeof(int) * (sz + 1));
    memset(up, 0, sizeof(int) * (sz + 1) * 20);
    memset(dfn, 0, sizeof(int) * (sz + 1));
    memset(ids, 0, sizeof(int) * (sz + 1));
    memset(mn, 0, sizeof(int) * (sz + 1) * 20);
    memset(mx, 0, sizeof(int) * (sz + 1) * 20);
    for (int i = 0; i <= sz; i++) {
        g[i].clear();
    }
}
void init_ST() {
    int t = log(n) / log(2) + 1;
    for (int i = 1; i <= n; ++i) {
        mn[i][0] = mx[i][0] = dfn[i];
    }
    for (int i = 1; i < t; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            mn[j][i] = min(mn[j][i - 1], mn[j + (1 << (i - 1))][i - 1]);
            mx[j][i] = max(mx[j][i - 1], mx[j + (1 << (i - 1))][i - 1]);
        }
    }
}
pii query(int l, int r) {
    int k = log(r - l + 1) / log(2);
    return {min(mn[l][k], mn[r - (1 << k) + 1][k]), max(mx[l][k], mx[r - (1 << k) + 1][k])};
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m >> q;
        init(n * 2 + 7);
        cnt = n;
        for (int i = 1; i <= n; ++i) fa[i] = i;
        for (int i = 1, u, v; i <= m; ++i) {
            cin >> u >> v;
            int fu = find(u), fv = find(v);
            if (fu != fv) {
                fa[fu] = fa[fv] = ++cnt;
                fa[cnt] = cnt;
                val[cnt] = i;
                g[cnt].push_back(fu);
                g[cnt].push_back(fv);
            }
        }
        dfs(cnt, 0);
        init_ST();
        for (int i = 1, l, r; i <= q; ++i) {
            cin >> l >> r;
            auto [left, right] = query(l, r);
            int father = lca(ids[left], ids[right]);
            if (i < q) cout << val[father] << ' ';
            else cout << val[father] << '\n';
        }
    }
}
