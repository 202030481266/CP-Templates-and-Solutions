class Solution {
public:
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        // 基环树
        vector<int> g[n];
        vector<int> cnt(n);

        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
            ++cnt[u];
            ++cnt[v];
        }
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (cnt[i] == 1) q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int& v : g[u]) {
                if (cnt[v] > 1) {
                    --cnt[v];
                    if (cnt[v] == 1)
                        q.push(v);
                }
            }
        }
        vector<int> ans(n);

        function<void(int, int, int)> dfs = [&](int u, int fa, int d) {
            ans[u] = d;
            for (int& v : g[u]) {
                if (cnt[v] == 1 && v != fa) {
                    dfs(v, u, d + 1);
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            if (cnt[i] > 1) {
                // cout <<i << ' ' << cnt[i] << endl;
                dfs(i, i, 0);
            }
        }
        return ans;
    }
};