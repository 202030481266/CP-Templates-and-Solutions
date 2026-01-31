class Solution {
    using pii = pair<int,int>;
public:
    int minReorder(int n, vector<vector<int>>& connections) {

        vector<pii> g[n];
        vector<int> rg[n];
        for (auto& e : connections) {
            int x = e[0], y = e[1];
            g[x].emplace_back(y, 0); // x -> y
            g[y].emplace_back(x, 1);
        }

        int ans = 0;
        function<void(int, int)> dfs = [&](int u, int fa) {
            for (auto [v, type] : g[u]) {
                if (v != fa) {
                    if (type == 0) ++ans;
                    dfs(v, u);
                }
            }
        };
        dfs(0, 0);
        return ans;
    }
};