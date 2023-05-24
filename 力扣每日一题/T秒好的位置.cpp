class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<int> g[n];
        for (auto &c : edges) {
            --c[0], --c[1];
            g[c[0]].emplace_back(c[1]);
            g[c[1]].emplace_back(c[0]);
        }
        double ans = 0;
        --target;
        function<void(int, int, int, double)> dfs = [&](int u, int fa, int dep, double prob) {
            if (ans > 0) return;
            if (dep == t) {
                if (u == target) ans = prob;
                return;
            }
            int siz = (u == 0 ? g[u].size() : g[u].size() - 1);
            if (siz) {
                for (auto v : g[u]) {
                    if (v == fa) continue;
                    dfs(v, u, dep + 1, prob / siz);
                }
            }
            else {
                if (u == target) ans = prob;
            }
        };
        dfs(0, 0, 0, 1);
        return ans;
    }
};