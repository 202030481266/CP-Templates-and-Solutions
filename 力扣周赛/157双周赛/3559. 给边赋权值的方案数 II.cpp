using ll = long long;
using pii = pair<int, int>;


static constexpr int maxn = 100007;
static constexpr int mod = 1e9 + 7;
vector<int> g[maxn];
int f[maxn][18], dep[maxn];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; i < 18; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int v : g[u]) {
        if (v != fa) dfs(v, u);
    }
}

int lca(int x, int y) {
    for (int i = 17; i >= 0; --i) {
	    if (dep[f[x][i]] >= dep[y]) {
            x = f[x][i];
	    }
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

void init(int n) {
    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        dep[i] = 0;
        for (int j = 0; j < 18; ++j) f[i][j] = 0;
    }
}

int quick_pow(int a, int b) {
    if (b < 0) return 0;
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = 1ll * a * a % mod;
    }
    return res % mod;
}

class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        init(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, 0);
        vector<int> ans;
        for (auto& q : queries) {
            int x = q[0], y = q[1];
            if (dep[x] < dep[y]) swap(x, y);
            int fa = lca(x, y);
            if (fa == y) {
                ans.push_back(quick_pow(2, dep[x] - dep[y] - 1));
            }
            else {
                ans.push_back(quick_pow(2, dep[x] + dep[y] - 2 * dep[fa] - 1));
            }
        }
        return ans;
    }
};