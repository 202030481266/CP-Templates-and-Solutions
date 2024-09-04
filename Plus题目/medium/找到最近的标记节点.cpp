#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {
        // 就是一个最短路问题
        vector<pii> g[n];
        for (auto e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v,w});
        }
        vector<ll> dis(n, 1e10);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
        dis[s] = 0;
        q.push({0, s});
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (d != dis[u]) continue;
            for (auto [v, w] : g[u]) {
                if (d + w < dis[v]) {
                    dis[v] = d + w;
                    q.push({dis[v], v});
                }
            }
        }
        ll ans = 1e10;
        for (int v : marked) 
            if (dis[v] < ans) ans = dis[v];
        return ans == 1e10 ? -1 : ans;
    }
};