class Solution {
    typedef long long ll;
    typedef pair<long long, long long> pll;
    static constexpr long long inf = 0x3f3f3f3f3f3f3f3f;
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pll>> g1(n), g2(n);
        for (auto &c : edges) {
            g1[c[0]].emplace_back(c[1], c[2]);
            g2[c[1]].emplace_back(c[0], c[2]);
        }
        vector<ll> dis1(n), dis2(n), dis3(n);
        // 最短路
        auto dijkstra = [&](vector<vector<pll>>& g, vector<ll>& dis, ll st) {
            priority_queue<pll, vector<pll>, greater<pll>> q;
            fill(dis.begin(), dis.end(), inf);
            dis[st] = 0LL;
            q.emplace(st, 0LL);
            while (!q.empty()) {
                auto [u, d] = q.top();
                q.pop();
                if (dis[u] != d) continue;
                for (auto [v, w] : g[u]) {
                    if (d + w < dis[v]) {
                        dis[v] = d + w;
                        q.emplace(v, dis[v]);
                    } 
                }
            }
        };
        dijkstra(g1, dis1, src1);
        dijkstra(g1, dis2, src2);
        dijkstra(g2, dis3, dest);
        if (dis1[dest] == inf || dis2[dest] == inf) return -1;
        long long ans = inf;
        for (int i = 0; i < n; ++i) {
            if (dis1[i] == inf || dis2[i] == inf || dis3[i] == inf) continue;
            ans = min(ans, dis1[i] + dis2[i] + dis3[i]);
        }
        return ans;
    }
};