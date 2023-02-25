// https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/


class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<int> dis(n + 1);
        vector<pair<int,int>> g[n + 1];
        vector<int> res(n + 1);

        for (auto c : edges) {
            g[c[0]].emplace_back(c[1], c[2]);
            g[c[1]].emplace_back(c[0], c[2]);
        }

        auto f = [&](int st) {
            fill(dis.begin(), dis.end(), INT_MAX);
            dis[st] = 0;
            priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> q;
            q.emplace(0, st);
            while (!q.empty()) {
                auto [c, u] = q.top();
                q.pop();
                if (dis[u] != c) continue;
                for (auto [v, w] : g[u]) {
                    if (dis[v] > dis[u] + w && dis[u] + w <= distanceThreshold) {
                        dis[v] = dis[u] + w;
                        q.emplace(dis[v], v);
                    }
                }
            }
            int ans = 0;
            for (int i = 0; i < n; ++i)
                if (dis[i] != INT_MAX) ++ans;
            res[st] = ans;
        };

        for (int i = 0; i < n; ++i)
            f(i);
        int mn = res[0], ans = 0;
        for (int i = 0; i < n; ++i) {
            if (res[i] <= mn) mn = res[i], ans = i;
        }
        return ans;
    }
};