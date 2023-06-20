class Solution {
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size(), dp[n][n];
        memset(dp, 0, sizeof(dp));
        vector<int> g[n];
        for (auto& c : edges) {
            g[c[0]].emplace_back(c[1]);
            g[c[1]].emplace_back(c[0]);
        }
        vector<int> fa(n, -1);
        vector<int> f(n, 0);
        int T = 0;
        for (int& c : nums) T ^= c;
        function<void(int, int)> dfs1 = [&](int u, int father) {
            f[u] = nums[u];
            for (int v : g[u]) {
                if (v != father) {
                    fa[v] = u;
                    dfs1(v, u);
                    f[u] ^= f[v];
                }
            }
        };
        dfs1(0, -1);
        function<void(int, int)> dfs2 = [&](int u, int father) {
            for (int v : g[u]) {
                if (v != father) {
                    dp[u][v] = f[v];
                    dp[v][u] = f[v] ^ T;
                    dfs2(v, u);
                }
            }
        };
        dfs2(0, -1);
        int res = INT_MAX;
        function<void(int, int, int, int)> dfs3 = [&](int u, int father, int son, int t) {
            for (int v : g[u]) {
                if (v != father && v != son) {
                    int mx = max({t, dp[u][v], T ^ dp[u][v] ^ t});
                    int mn = min({t, dp[u][v], T ^ dp[u][v] ^ t});
                    res = min(res, mx - mn);
                    dfs3(v, u, son, t);
                }
            }
        };
        function<void(int, int)> dfs = [&](int u, int father) {
            for (int v : g[u]) {
                // 两个顶点开始搜索
                if (v != father) {
                    dfs3(v, -1, u, T ^ dp[u][v]);
                    dfs3(u, -1, v, dp[u][v]);
                    dfs(v, u);
                }
            }
        };
        dfs(0, -1);
        return res;
    }
};