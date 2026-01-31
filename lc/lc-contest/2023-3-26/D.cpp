class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        unordered_set<int> g[n];
        for (auto e : edges) {
            g[e[0]].emplace(e[1]);
            g[e[1]].emplace(e[0]);
        }

        vector<bool> del(n, false);
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (g[i].size() == 1 && coins[i] == 0) q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            del[u] = true;
            for (int v : g[u]) {
                g[v].erase(u);
                if (coins[v] == 0 && g[v].size() == 1) {
                    q.push(v);
                }
            }
        }
        int T = 2;
        while (T--) {
            for (int i = 0; i < n; ++i) {
                if (!del[i] && g[i].size() == 1) del[i] = true;
            }
            for (int i = 0; i < n; ++i) {
                if (del[i]) {
                    for (int v : g[i]) {
                        g[v].erase(i);
                    }
                }
            }
        }
        int ans = 0;
        for (auto e : edges) {
            if (!del[e[0]] && !del[e[1]]) ans += 2;
        }
        return ans;
    }
};