class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> vis(n);
        vector<int> color(n);

        function<bool(int,int)> dfs = [&](int u,int c) -> bool {
            if (vis[u]) {
                if (color[u] == c) return true;
                else return false;
            }
            vis[u] = true;
            color[u] = c;
            bool res = true;
            for (auto v : graph[u]) {
                res = (res && dfs(v, c ^ 1));
            }
            return res;
        };
        bool res = true;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) res = (res && dfs(i, 0));
        }
        return res;
    }
};