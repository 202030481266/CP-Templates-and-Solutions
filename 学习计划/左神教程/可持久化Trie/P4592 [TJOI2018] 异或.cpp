// https://www.luogu.com.cn/problem/P4592

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e5 + 7;
const int N = maxn * 70;
const int B = 30;
int n, m, tot, dfn;
int id[maxn], a[maxn], dep[maxn], fa[maxn][20], node[maxn], siz[maxn];
int root1[maxn], root2[maxn], tree[N][2], cnt[N];
vector<int> g[maxn];

int insert(int num, int x) {
    int rt = ++tot;
    tree[rt][0] = tree[x][0];
    tree[rt][1] = tree[x][1];
    cnt[rt] = cnt[x] + 1;
    for (int i = B, pre = rt, cur, b; i >= 0; --i) {
        b = (num >> i) & 1;
        x = tree[x][b];
        cur = ++tot;
        tree[cur][0] = tree[x][0];
        tree[cur][1] = tree[x][1];
        cnt[cur] = cnt[x] + 1;
        tree[pre][b] = cur;
        pre = cur;
    }
    return rt;
}

void dfs1(int u, int father) {
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    root1[u] = insert(a[u], root1[father]);
    id[u] = ++dfn;
    node[dfn] = u;
    siz[u] = 1;
    for (int i = 1; i < 20; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int v : g[u]) {
        if (v == father) continue;
        dfs1(v, u);
        siz[u] += siz[v];
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    }
    return fa[x][0];
}

int query(int num, int x, int y) {
    int res = 0;
    for (int i = B, b; i >= 0; --i) {
        b = (num >> i) & 1;
        if (cnt[tree[y][b ^ 1]] - cnt[tree[x][b ^ 1]] > 0) {
            res |= 1 << i;
            x = tree[x][b ^ 1];
            y = tree[y][b ^ 1];
        } else {
            x = tree[x][b];
            y = tree[y][b];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i) {
        root2[i] = insert(a[node[i]], root2[i-1]);
    }
    for (int i = 1, op, x, y, z; i <= m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> x >> z;
            int l = id[x]-1, r = id[x]+siz[x]-1;
            cout << query(z, root2[l], root2[r]) << '\n';
        }
        else {
            cin >> x >> y >> z;
            int f = lca(x, y);
            int mx_1 = query(z, root1[fa[f][0]], root1[x]);
            int mx_2 = query(z, root1[fa[f][0]], root1[y]);
            cout << max(mx_1, mx_2) << '\n';
        }
    }
}
