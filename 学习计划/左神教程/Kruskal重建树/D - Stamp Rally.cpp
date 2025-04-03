// https://atcoder.jp/contests/agc002/tasks/agc002_d

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 1e5 + 7;
const int N = maxn << 1;

int n, m, q;
int dep[N], fa[N], val[N], up[N][20], siz[N], cnt = 0;
vector<int> g[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void dfs (int u, int father) {
    dep[u] = dep[father] + 1;
    up[u][0] = father;
    if (u <= n) siz[u] = 1;
    for (int i = 1; i < 20; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v : g[u]) {
        dfs(v, u);
        siz[u] += siz[v];
    }
}
int getBottleneck(int x, int limit) {
    for (int i = 19; i >= 0; --i) {
        if (up[x][i] > 0 && val[up[x][i]] <= limit) {
            x = up[x][i];
        }
    }
    return x;
}
int check(int x, int y, int limit) {
    int fx = getBottleneck(x, limit), fy = getBottleneck(y, limit);
    if (fx == fy) return siz[fx];
    return siz[fx] + siz[fy];
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
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
    cin >> q;
    for (int i = 1, u, v, t; i <= q; ++i) {
        cin >> u >> v >> t;
        int l = 0, r = m + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(u, v, mid) >= t) {
                r = mid;
            } else {
                l = mid;
            }
        }
        cout << r << '\n';
    }
}