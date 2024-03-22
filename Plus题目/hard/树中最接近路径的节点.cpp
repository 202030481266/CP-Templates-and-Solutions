const int N = 1010, LG = 10;

int par[N][LG + 1], dep[N];

class Solution {
public:
    vector<vector<int>> g;
    void dfs(int u, int p = 0) {
        par[u][0] = p;
        dep[u] = dep[p] + 1;
        for (int i = 1; i <= LG; i++) 
            par[u][i] = par[par[u][i - 1]][i - 1];
        for (auto v: g[u]) if (v != p) {
            dfs(v, u);
        }
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
        if (u == v) return u;
        for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
        return par[u][0];
    }
    vector<int> closestNode(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        // init
        g.resize(n);
        memset(par, 0, sizeof(par));
        memset(dep, 0, sizeof(dep));
        // build the graph
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(0, 0);  // 0 ~ n - 1

        vector<int> ans;
        for (auto& q : query) {
            int a = q[0], b = q[1], c = q[2];
            if (dep[b] > dep[a]) swap(a, b);
            int x = lca(a, b);
            if (x == b) {
                int y = lca(b, c);
                if (y == c || y != b && y != c) {
                    ans.push_back(b);
                }
                else {
                    ans.push_back(lca(a, c));
                }
            }
            else {
                int y = lca(x, c);
                if ((y != c && y != x) || (c == y)) {
                    ans.push_back(x);
                }
                else {
                    int s = lca(a, c), t = lca(b, c);
                    if (s == t) {
                        ans.push_back(x);
                    }
                    else if (s != x) {
                        ans.push_back(s);
                    }
                    else {
                        ans.push_back(t);
                    }
                }
            }
        }
        return ans;
    }
};