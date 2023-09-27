class Solution {
    vector<vector<pair<int,int>>> G;
    int n, f[10010][15], g[10010][26], d[10010];
public:
    void dfs(int u, int fa, int dep, vector<int>& val) {
        d[u] = dep;
        f[u][0] = fa;
        for (int i = 0; i < 26; ++i)
            g[u][i] = val[i];
        for (int i = 1; (1 << i) <= d[u]; ++i)
            f[u][i] = f[f[u][i - 1]][i - 1];
        for (auto [v, w] : G[u]) {
            if (v != fa) {
                ++val[w];
                dfs(v, u, dep + 1, val);
                --val[w];
            }
        }
    }
    int lca(int x, int y) {
        if (d[x] > d[y]) swap(x, y);  // d[y] >= d[x]
        for (int i = 14; i >= 0; --i)
            if (d[f[y][i]] >= d[x]) y = f[y][i];
        if (y == x) return x;
        for (int i = 14; i >= 0; --i)
            if (f[x][i] != f[y][i])
                x = f[x][i], y = f[y][i];
        return f[x][0];
    }
    vector<int> minOperationsQueries(int N, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        n = N;
        G.resize(n);
        for (auto& c : edges) {
            G[c[0]].emplace_back(c[1], c[2] - 1);
            G[c[1]].emplace_back(c[0], c[2] - 1);
        }
        vector<int> val(26);
        dfs(0, 0, 1, val);
        vector<int> ans;
        for (auto& q : queries) {
            int ff = lca(q[0], q[1]), mx = 0;
            for (int i = 0; i < 26; ++i) 
                mx = max(mx, g[q[0]][i] + g[q[1]][i] - 2 * g[ff][i]);
            ans.push_back(d[q[0]] + d[q[1]] - 2 * d[ff] - mx);
        }
        return ans;
    }
};