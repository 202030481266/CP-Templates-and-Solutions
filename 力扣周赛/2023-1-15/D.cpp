class Solution {
public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        vector<vector<int>> g(n);
        vector<long long> dp(n), ans(n);
        vector<vector<long long>> pre(n);

        for (auto c : edges) {
            g[c[0]].emplace_back(c[1]);
            g[c[1]].emplace_back(c[0]);
        }
        function<void(int,int)> dfs = [&](int u, int fa) {
            dp[u] = price[u];
            for (auto v : g[u]) {
                if (v == fa) continue;
                dfs(v, u);
                dp[u] = max(dp[u], dp[v] + price[u]);
            }
        };
        function<void(int,int)> solve = [&](int u, int fa) {
            pre[u].emplace_back(price[u]);
            dp[u] = price[u];
            for (auto v : g[u]) {
                dp[u] = max(dp[u], dp[v] + price[u]);
                pre[u].emplace_back(dp[u]);
            }
            ans[u] = dp[u];
            long long x = 0;
            for (int i = g[u].size() - 1; i >= 0; i--) {
                int v = g[u][i];
                dp[u] = max(pre[u][i], x);
                x = max(x, dp[v] + price[u]);
                if (v != fa) solve(v, u);
            }
        };
        // get the root as 0
        dfs(0, -1);
        solve(0, -1);
        long long res = 0;
        for (int i = 0; i < n; i++) {
            cout << ans[i] << endl;
            res = max(res, ans[i] - price[i]);
        }
        return res;
    }
};