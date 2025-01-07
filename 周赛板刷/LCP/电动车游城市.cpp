class Solution {
public:
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        int n = charge.size(), dis[n][cnt + 1], vis[n][cnt + 1];
        pair<int, int> pre[n][cnt + 1];
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));

        vector<pair<int, int>> g[n];

        for (auto& e : paths) {
            int x = e[0], y = e[1], cost = e[2];
            if (cost <= cnt) {
                g[x].emplace_back(y, cost);
                g[y].emplace_back(x, cost);
            }
        }


        // 使用自定义的闭包函数
        auto cmp = [&](const pair<int, int>& a, const pair<int, int>& b) -> bool {
            return dis[a.first][a.second] > dis[b.first][b.second];
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);  // 注意一定要判重，这个堆不能同时将相同的状态放到一起
        dis[start][0] = 0;
        q.emplace(start, 0);
        while (!q.empty()) {
            auto [u, t] = q.top();
            q.pop();
            vis[u][t] = 0;
            // 考虑自身
            for (int i = t + 1; i <= cnt; ++i) {
                if (dis[u][i] > dis[u][t] + charge[u] * (i - t)) {
                    dis[u][i] = dis[u][t] + charge[u] * (i - t);
                    if (!vis[u][i]) {
                        vis[u][i] = 1;
                        q.emplace(u, i);
                    }
                }
            }
            // 考虑 u -> v
            for (pair<int, int>& p : g[u]) {
                int v = p.first, c = p.second;
                for (int i = max(c, t); i <= cnt; ++i) {
                    if (dis[v][i - c] > dis[u][t] + charge[u] * (i - t) + c) {
                        dis[v][i - c] = dis[u][t] + charge[u] * (i - t) + c;
                        if (!vis[v][i - c]) {
                            vis[v][i - c] = 1;
                            q.emplace(v, i - c);
                        }
                    }
                }
            }
        }
        return *min_element(dis[end], dis[end] + cnt + 1);
    }
};