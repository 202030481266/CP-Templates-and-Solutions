class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        // 一个操作可以使得相邻节点的价格减半，选择一些不相邻的节点，那么一个明显的做法就是进行二分图的染色来构造出两种情况
        // 但显然是不对的，因为一个点覆盖对应了一个值，按照上面的做法只能选择出比较优秀的情况，但实际这是错误的，因为这时np完全的
        vector<vector<int>> g(n);
        for (auto &c : edges) g[c[0]].emplace_back(c[1]), g[c[1]].emplace_back(c[0]);
        vector<int> path;
        vector<int> cnt(n);
        bool flag = false;
        function<void(int, int, int)> dfs = [&](int u, int fa, int target) {
            if (flag) return;
            if (u == target) {
                flag = true;
                for (int v : path) ++cnt[v];
                return;
            }
            for (int v : g[u]) {
                if (v != fa) {
                    path.emplace_back(v);
                    dfs(v, u, target);
                    path.pop_back();
                }
            }
        }; 
        for (auto &c : trips) {
            flag = false;
            path.emplace_back(c[0]);
            dfs(c[0], -1, c[1]);
            path = vector<int>{};
        }
        vector dp(n, vector<int>(2));
        function<void(int, int)> f = [&](int u, int fa) {
            dp[u][0] += cnt[u] * price[u];
            dp[u][1] += cnt[u] * (price[u] / 2);
            for (int v : g[u]) {
                if (v != fa) {
                    f(v, u);
                    dp[u][0] += min(dp[v][0], dp[v][1]);
                    dp[u][1] += dp[v][0];
                }
            }
        };
        f(0, -1);
        return min(dp[0][0], dp[0][1]);
    }
};