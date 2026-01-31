// 树链剖分解决LCA
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 5e5 + 7;
int n, m, root, p;
int dep[maxn], fa[maxn], dfn[maxn], ids[maxn], siz[maxn];
int son[maxn], top[maxn], tot;
vector<int> g[maxn];

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    fa[u] = f;
    for (int v : g[u]) {
        if (v != f) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
}

void dfs2(int u, int f) {
    dfn[u] = ++tot;
    ids[tot] = u;
    top[u] = f;
    if (!son[u]) return;
    dfs2(son[u], f); 
    for (int v : g[u]) {
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] <= dep[top[v]]) v = fa[top[v]];
        else u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> root;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(root, 0);
    dfs2(root, root);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}
