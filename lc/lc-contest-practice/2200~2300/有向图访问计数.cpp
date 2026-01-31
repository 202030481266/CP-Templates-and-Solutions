// 基环树
class Solution {
public:
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();

        // 一定存在一个环
        vector<int> g[n];
        vector<int> rg[n];
        vector<int> in(n, 0);
        for (int i = 0; i < n; ++i) {
            g[i].push_back(edges[i]);
            rg[edges[i]].push_back(i);
            ++in[edges[i]];
        }

        // topu sort
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (in[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int& v : g[u]) {
                --in[v];
                if (in[v] == 0) q.push(v);
            }
        }

        // 遍历环 和 树链
        vector<int> ans(n);
        vector<int> vis(n, 0);
        function<void(int,int)> dfs = [&](int u, int dis) {
            ans[u] = dis;
            for (int& v : rg[u])
                if (!in[v])
                    dfs(v, dis + 1);
        };
        for (int i = 0; i < n; ++i) {
            if (in[i] && !vis[i]) {
                int res = 1, x = edges[i];
                vis[i] = 1;
                while (x != i) {
                    vis[x] = 1;
                    ++res; 
                    x = edges[x];
                }
                dfs(i, res);
                x = edges[i];
                while (x != i) {
                    dfs(x, res); 
                    x = edges[x];
                }
            }
        }
        return ans;
    }
};