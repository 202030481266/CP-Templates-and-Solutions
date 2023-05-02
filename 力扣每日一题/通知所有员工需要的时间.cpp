class Solution {
    typedef long long ll;
    typedef pair<long long, long long> pll;
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        if (n == 1) return 0;
        vector<pll> g[n];
        vector<ll> dis(n, 2e10);
        // 建图
        for (int i = 0; i < n; ++i) 
            if (manager[i] != -1) {
                int cost = informTime[manager[i]];
                g[manager[i]].emplace_back(i, cost);
            }
        // 最短路
        priority_queue<pll, vector<pll>, greater<pll>> q;
        q.emplace(0, headID);
        dis[headID] = 0;
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (dis[u] != d) continue;
            for (auto [v, w] : g[u]) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.emplace(dis[v], v);
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i < n; ++i) 
            if (dis[i] != 2e10) ans = max(ans, dis[i]);
        return ans;
    }
};