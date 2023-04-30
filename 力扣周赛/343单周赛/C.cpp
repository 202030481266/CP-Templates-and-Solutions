class Solution {
    typedef pair<long long, long long> pll;
    typedef pair<int, int> pii;
    typedef long long ll;
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        // 使用special建图，然后跑最短路
        map<pii, int> idx;
        map<int, pii> point;
        set<pii> s;
        s.emplace(start[0], start[1]);
        s.emplace(target[0], target[1]);
        for (auto &c : specialRoads) {
            s.emplace(c[0], c[1]);
            s.emplace(c[2], c[3]);
        }
        int tot = 0;
        for (auto p : s) {
            idx[p] = ++tot;
            point[tot] = p;
        }
        auto cal = [&](int x1, int y1, int x2, int y2) -> ll {
            return 1ll * abs(x1 - x2) + 1ll * abs(y1 - y2);
        };
        // 建图
        vector<vector<pll>> g(tot + 1);
        for (auto u : s)
            for (auto v : s) 
                g[idx[u]].emplace_back(1ll * idx[v], cal(u.first, u.second, v.first, v.second));
        for (auto &c : specialRoads)
            g[idx[{c[0], c[1]}]].emplace_back(1ll * idx[{c[2], c[3]}], 1ll * c[4]);
        // 最短路
        priority_queue<pll, vector<pll>, greater<pll>> q;
        vector<long long> dis(tot + 1, 0x3f3f3f3f3f3f3f3f);
        q.emplace(0, idx[{start[0], start[1]}]);
        dis[idx[{start[0], start[1]}]] = 0;
        while (!q.empty()) {
            auto [cost, u] = q.top();
            q.pop();
            if (dis[u] != cost) continue;
            for (auto [v, w] : g[u]) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.emplace(dis[v], v);
                }
            }
        }
        return dis[idx[{target[0], target[1]}]];
    }
};