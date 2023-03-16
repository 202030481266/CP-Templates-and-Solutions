// https://leetcode.cn/problems/minimize-malware-spread-ii/



class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        vector<vector<int>> g(n);
        unordered_set<int> virus;

        for (auto c : initial) virus.emplace(c);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (graph[i][j]) {
                    g[i].emplace_back(j);
                    g[j].emplace_back(i);
                }

        vector<bool> vis(n);
        vector<int> cnt(n);
        vector<vector<int>> spread(n);
        function<void(int, int)> dfs = [&](int u, int f) {
            for (int v : g[u]) {
                if (!vis[v] && !virus.count(v)) {
                    vis[v] = true;
                    spread[f].emplace_back(v);
                    ++cnt[v];
                    dfs(v, f);
                }
            }
        };
        for (auto u : initial) {
            fill(vis.begin(), vis.end(), false);
            dfs(u, u);
        }
        int res = 0, ans = 0;
        sort(initial.begin(), initial.end());
        for (auto u : initial) {
            int tmp = 0;
            for (auto v : spread[u]) {
                if (cnt[v] == 1)  // only spread by u
                    ++tmp;
            }
            if (tmp > res) {
                res = tmp;
                ans = u;
            }
        }
        return res == 0 ? initial[0] : ans;
    }
};