// 树上静态区间第k小

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 2e5 + 7;
const int N = maxn * 27;

int n, m, lastans, tot, root[maxn], a[maxn], b[maxn], bn;
int ls[N], rs[N], sz[N];
int dep[maxn], f[maxn][20];
vector<int> g[maxn];

int get_idx(int val) {
    return lower_bound(b + 1, b + bn + 1, val) - b; // 1-based
}
int build(int l, int r) {
    int rt = ++tot;
    if (l == r) return rt;
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    return rt;
}
int update(int rt, int l, int r, int p) {
    int c = ++tot;
    ls[c] = ls[rt], rs[c] = rs[rt], sz[c] = sz[rt];
    if (l == r) {
        sz[c] += 1;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p);
    else rs[c] = update(rs[c], mid + 1, r, p);
    sz[c] = sz[ls[c]] + sz[rs[c]];
    return c;
}
int query(int u, int v, int fa, int ff, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int l_size = sz[ls[u]] + sz[ls[v]] - sz[ls[fa]] - sz[ls[ff]]; //树上的信息计算
    if (l_size >= k) return query(ls[u], ls[v], ls[fa], ls[ff], l, mid, k);
    else return query(rs[u], rs[v], rs[fa], rs[ff], mid + 1, r, k - l_size);
}
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    a[u] = get_idx(a[u]);
    root[u] = update(root[fa], 1, bn, a[u]);
    for (int i = 1; i < 18; ++i) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (int v : g[u]) {
        if (v != fa) {
            dfs(v, u);
        }
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 17; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 17; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sort(b + 1, b + n + 1);
    bn = unique(b + 1, b + n + 1) - b - 1;
    root[0] = build(1, bn);
    dfs(1, 0);
    for (int i = 1, u, v, k; i <= m; ++i) {
        cin >> u >> v >> k;
        u ^= lastans;
        int fa = lca(u, v);
        int res = query(root[u], root[v], root[fa], root[f[fa][0]], 1, bn, k);
        lastans = b[res];
        cout << lastans << '\n';
    }
}