// 树形DP
class Solution {
    unordered_set<long long> mp;
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        vector<int> f(n), dp(n);
        vector<int> g[n];
        for (auto& c : edges) {
            g[c[0]].push_back(c[1]);
            g[c[1]].push_back(c[0]);
            mp.insert(1ll * c[0] * 100000 + c[1]);
        }
        function<void(int,int)> dfs_f = [&](int u, int fa) {
            for (int& v : g[u]) {
                if (v == fa) continue;
                dfs_f(v, u);
                // u->v
                if (mp.count(1ll * u * 100000 + v)) {
                    f[u] += f[v];
                }
                else {
                    f[u] += f[v] + 1;
                }
            }
        };
        dfs_f(0, -1);
        dp[0] = f[0];
        function<void(int,int)> dfs = [&](int u, int fa) {
            if (fa != -1) {
                // u -> fa
                if (mp.count(1ll * u * 100000 + fa)) dp[u] = dp[fa] - 1;
                else dp[u] = dp[fa] + 1;
            }
            for (int& v : g[u]) {
                if (v == fa) continue;
                dfs(v, u);
            }
        };
        dfs(0, -1);
        return dp;
    }
};