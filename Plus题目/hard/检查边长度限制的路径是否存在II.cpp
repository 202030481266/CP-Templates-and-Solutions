// 两种做法
// 最小生成树 + 树上倍增
// 可持久化并查集
class UnionFind {
    vector<int> parent, size;
    int n, setCount;

public:
    UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    bool connected(int x, int y) { return find(x) == find(y); }
};

const int N = 1e4 + 5, LG = 14;
int par[N][LG + 1], dep[N], sz[N], f[N][LG + 1];

class DistanceLimitedPathsExist {
public:
    vector<vector<pair<int, int>>> g;
    UnionFind* un;
    void dfs(int u, int p, int val) {
        f[u][0] = val;
        par[u][0] = p;
        dep[u] = dep[p] + 1;
        sz[u] = 1;
        for (int i = 1; i <= LG; ++i)
            par[u][i] = par[par[u][i - 1]][i - 1];
        for (int i = 1; i <= LG; ++i)
            f[u][i] = max(f[u][i - 1], f[par[u][i - 1]][i - 1]);
        for (pair<int, int>& e : g[u]) {
            int v = e.first, c = e.second;
            if (v != p) {
                dfs(v, u, c);
                sz[u] += sz[v];
            }
        }
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v])
            swap(u, v); // u is always the biggest one
        int x = 0, y = 0;
        for (int k = LG; k >= 0; --k) {
            if (dep[par[u][k]] >= dep[v]) {
                x = max(x, f[u][k]);
                u = par[u][k];
            }
        }
        if (u == v)
            return x;
        for (int k = LG; k >= 0; --k) {
            if (par[u][k] != par[v][k]) {
                x = max(x, f[u][k]);
                y = max(y, f[v][k]);
                u = par[u][k];
                v = par[v][k];
            }
        }
        return max(max(x, y), max(f[u][0], f[v][0])); // 这里还有最后一步！别漏了，调了两个小时
    }
    int id = 0;
    DistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList) {
        memset(par, 0, sizeof(par));
        memset(f, 0, sizeof(f));
        memset(dep, 0, sizeof(dep));
        memset(sz, 0, sizeof(sz));
        g.resize(n);
        // 最小生成树
        un = new UnionFind(n);
        sort(edgeList.begin(), edgeList.end(),
             [&](vector<int>& x, vector<int>& y) { return x[2] < y[2]; });
        for (vector<int>& e : edgeList) {
            int u = e[0], v = e[1];
            if (un->connected(u, v))
                continue;
            un->unite(u, v);
            g[u].push_back({v, e[2]});
            g[v].push_back({u, e[2]});
        }
        for (int i = 0; i < n; ++i) {
            if (!sz[i]) {
                dfs(i, i, 0);
            }
        }
    }

    bool query(int p, int q, int limit) {
        if (!un->connected(p, q))
            return false;
        int res = lca(p, q);
        return res < limit;
    }
};

/**
 * Your DistanceLimitedPathsExist object will be instantiated and called as
 * such: DistanceLimitedPathsExist* obj = new DistanceLimitedPathsExist(n,
 * edgeList); bool param_1 = obj->query(p,q,limit);
 */


