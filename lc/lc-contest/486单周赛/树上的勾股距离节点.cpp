#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;

const int N = 1e5 + 9;

vector<int> g[N];
int par[N][20], dep[N], sz[N], st[N], en[N], T;
void dfs(int u, int pre) {
    par[u][0] = pre;
    dep[u] = dep[pre] + 1;
    sz[u] = 1;
    st[u] = ++T;
    for (int i = 1; i <= 18; i++) par[u][i] = par[par[u][i - 1]][i - 1];
    for (auto v : g[u]) {
        if (v == pre) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    en[u] = T;
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 18; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = 18; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}

void clear(int n) {
    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        sz[i] = dep[i] = st[i] = en[i] = 0;
        for (int j = 0; j < 20; ++j) par[i][j] = 0;
    }
    T = 0;
}

bool check(ll a, ll b, ll c) {
    if (b * b == a * a + c * c) return true;
    if (a * a == b * b + c * c) return true;
    if (c * c == a * a + b * b) return true;
    return false;
}

class Solution {
public:
    int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {
        clear(n);
        for (auto& e : edges) {
            int u = e[0] + 1, v = e[1] + 1;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        ++x;
        ++y;
        ++z;
        dfs(1, 0);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int fx = lca(i, x);
            ll dx = abs(dep[i] - dep[fx]) + abs(dep[x] - dep[fx]);
            int fy = lca(i, y);
            ll dy = abs(dep[i] - dep[fy]) + abs(dep[y] - dep[fy]);
            int fz = lca(i, z);
            ll dz = abs(dep[i] - dep[fz]) + abs(dep[z] - dep[fz]);
            if (check(dx, dy, dz)) ++ans;
        }
        return ans;
    }
};

