class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> g(n);

        for (auto e : edges) {
            g[e[0]].emplace(e[1]);
            g[e[1]].emplace(e[0]);
        }
        // vector<bool> vis(n, false);
        // function<bool(int, int)> dfs = [&](int u, int fa) -> bool {
        //     for (int v : g[u]) {
        //         if (v == fa) continue;
        //         if (!vis[u]) {
        //             vis[u] = true;
        //             if (dfs(v, u))
        //                 return true;
        //         }
        //         else return true;
        //     }
        //     return false;
        // };
        // bool flag = false;
        // for (int i = 0; i < n; ++i) {
        //     if (!vis[i]) {
        //         vis[i] = true;
        //         if (dfs(i, i)) {
        //             flag = true;
        //             break;
        //         }
        //     }
        // }
        // cout << flag << endl;
        // if (!flag) return -1; // no circle

        vector<int> dis(n, 0);
        auto f = [&](int x, int y) {
            fill(dis.begin(), dis.end(), 0x3f3f3f3f);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
            dis[x] = 0;
            q.emplace(dis[x], x);
            while (!q.empty()) {
                auto [d, u] = q.top();
                q.pop();
                if (dis[u] != d) continue;
                if (u == y) return dis[u];
                for (int v : g[u]) {
                    if (dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        q.emplace(dis[v], v);
                    }
                }
            }
            return dis[y];
        };

        // delete the edges and caculate the shortest path
        int ans = INT_MAX;
        for (auto e : edges) {
            g[e[0]].erase(e[1]);
            g[e[1]].erase(e[0]);
            int res = f(e[0], e[1]);
            if (res != 0x3f3f3f3f) {
                ans = min(ans, 1 + res);
            }
            g[e[0]].emplace(e[1]);
            g[e[1]].emplace(e[0]);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};