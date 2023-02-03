class Solution {
public:
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        // directed
        vector<int> g[n]; 
        vector<int> vis(n, false);

        for (auto c : graph) 
            g[c[0]].emplace_back(c[1]);
        queue<int> q;
        q.emplace(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == target) return true;
            for (auto v : g[u])
                if (!vis[v]) q.emplace(v), vis[v] = true;
        }
        return false;
    }
};