// https://www.luogu.com.cn/problem/P9638

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 4e5 + 7;
const int N = maxn * 2;
int n, m, q, fa[N], dep[N], siz[N], up[N][20], cnt = 0;
int val[N], edge2node[N];
vector<int> g[N];
struct edge {
    int u, v, w, id;
} edges[maxn];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void dfs(int u, int father) {
    dep[u] = dep[father] + 1;
    if (u <= n) siz[u] = 1;
    up[u][0] = father;
    for (int i = 1; i < 20; ++i) 
        up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v : g[u]) {
        dfs(v, u);
        siz[u] += siz[v];
    }
}
int solve(int x, int limit) {
    for (int i = 19; i >= 0; --i) {
        if (up[x][i] > 0 && val[up[x][i]] >= limit) {
            x = up[x][i];
        }
    }
    return x;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> q;
    cnt = n;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        edges[i].id = i;
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges + 1, edges + 1 + m, [](edge a, edge b) {
        return a.w > b.w; // 降序
    });
    for (int i = 1; i <= m; ++i) {
        int fu = find(edges[i].u), fv = find(edges[i].v);
        if (fu != fv) {
            int tmp = ++cnt;
            fa[tmp] = tmp;
            val[tmp] = edges[i].w;
            edge2node[edges[i].id] = tmp;
            fa[fu] = fa[fv] = tmp;
            g[tmp].push_back(fu);
            g[tmp].push_back(fv);
        }
    }
    for (int i = 1; i <= cnt; ++i) {
        if (i == find(i)) dfs(i, 0);
    }
    for (int i = 1, op, limit = 0, x, y; i <= q; ++i) {
        cin >> op;
        if (op == 1) cin >> limit;
        else if (op == 2) {
            cin >> x;
            int res = solve(x, limit);
            cout << siz[res] << '\n';
        }
        else {
            cin >> x >> y;
            int node = edge2node[x];
            if (node) val[node] = y;
        }
    }
}