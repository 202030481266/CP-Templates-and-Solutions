#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pii>> g(n), rg(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w * 2);
        }
        vector<int> dis(n, inf);
        auto dijkstra = [&](vector<int>& dist, int st, vector<vector<pii>>& graph) {
            priority_queue<pii, vector<pii>, greater<pii>> q;
            q.emplace(0, st);
            dist[st] = 0;
            while (!q.empty()) {
                auto [d, u] = q.top();
                q.pop();
                if (d != dist[u]) continue;
                for (auto [v, w] : graph[u]) {
                    if (dist[v] > d + w) {
                        dist[v] = d + w;
                        q.emplace(dist[v], v);
                    }
                }
            }
        };
        dijkstra(dis, 0, g);
        return dis[n-1] == inf ? -1 : dis[n-1];
    }
};