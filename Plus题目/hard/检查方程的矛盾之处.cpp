const double eps = 1e-5;
bool equal(double x, double y) {
    return fabs(x - y) < eps;
}
class Solution {
public:
    bool checkContradictions(vector<vector<string>>& equations, vector<double>& values) {
        unordered_map<string, int> id;
        int n = 0, m = values.size();
        for (auto& e : equations) {
            if (!id.count(e[0])) id[e[0]] = n++;
            if (!id.count(e[1])) id[e[1]] = n++;
        }
        vector<int> g[n];
        vector exi(n, vector<double>(n, 0));
        for (int i = 0; i < m; ++i) {
            vector<string>& e = equations[i];
            int u = id[e[0]], v = id[e[1]];
            if (u == v) {
                // 自环
                if (!equal(values[i], 1.0)) return true;
            }
            else if (exi[u][v] > 0) {
                // u / v = values[i]
                if (!equal(exi[u][v], values[i])) return true; // 重边
            }
            else {
                exi[u][v] = values[i];
                exi[v][u] = 1.0 / values[i];
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }

        vector<bool> vis(n);
        vector<double> val(n);
        function<bool(int)> dfs = [&](int u) -> bool {
            for (int& v : g[u]) {
                if (vis[v]) {
                    if (!equal(val[u], val[v] * exi[u][v]))
                        return true;
                }
                else {
                    // u / v = exi[u][v]
                    vis[v] = true;
                    val[v] = val[u] / exi[u][v];
                    if (dfs(v))
                        return true;
                }
            }
            return false;
        };
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                vis[i] = true;
                val[i] = 1.0;
                if (dfs(i))
                    return true;
            }
        }
        return false;
    }
};