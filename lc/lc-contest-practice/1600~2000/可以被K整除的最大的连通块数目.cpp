class Solution {
    vector<vector<int>> g;
    int ans = 0;
public:
    int dfs(int u, int fa, vector<int>& values, int k) {
        int val = values[u] % k;
        for (int& v : g[u]) {
            if (v != fa) {
                int res = dfs(v, u, values, k);
                if (res > 0) {
                    val = (val + res) % k;
                }
            }
        }
        if (val == 0) ++ans;
        return val;
    }
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        g.resize(n);

        // 建树
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        dfs(0, 0, values, k);
        return ans;
    }
};