class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        int ans = -1;

        // 拓扑排序把图简化（简化的神器）
        vector<int> du(n);
        for (int v : edges)
            if (v != -1) ++du[v];
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (du[i] == 0) q.emplace(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int v = edges[u];
            if (v != -1) {
                --du[v];
                if (du[v] == 0) q.emplace(v);
            }
        }

        // 剩下的都是环，然后就计算一下环的大小即可
        vector<int> vis(n, false);
        function<void(int, int)> dfs = [&](int u, int depth) {
            vis[u] = true;
            int v = edges[u];
            if (v != -1) {
                if (!vis[v])
                    dfs(v, depth + 1);
                else ans = max(ans, depth + 1);
            }
        };
        vector<int> tmp;
        for (int i = 0; i < n; ++i) {
            if (du[i] > 0 && !vis[i]) dfs(i, 0);
        }
        return ans;
    }
};