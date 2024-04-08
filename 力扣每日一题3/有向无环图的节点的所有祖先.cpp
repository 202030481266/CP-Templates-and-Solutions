int add[1010];
int vis[1010];

class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<int> g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[v].push_back(u);
        }       

        vector<vector<int>> ans(n);
        memset(vis, 0, sizeof(vis));

        function<void(int)> dfs = [&](int u) {
            if (vis[u]) return;
            vis[u] = 1;
            for (int& v : g[u]) {
                dfs(v);
                ans[u].push_back(v);
            }
            memset(add, 0, sizeof(add));
            for (int& v : g[u])
                add[v] = 1;
            for (int& v : g[u]) {
                for (int& x : ans[v]) { 
                    if (!add[x]) {
                        add[x] = 1;
                        ans[u].push_back(x);
                    }
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            dfs(i);
            sort(ans[i].begin(), ans[i].end());
        }
        
        return ans;
    }
};