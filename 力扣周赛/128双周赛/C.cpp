class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        map<pair<int, int>, int> value;
        vector<pair<int, int>> g[n];

        for (auto& e : edges) {
            int u = e[0], v = e[1], c = e[2];
            if (u > v) swap(u, v);
            if (value.count({u, v})) 
                value[{u, v}] = min(value[{u, v}], c);
            else value[{u, v}] = c;
        }
        for (auto it = value.begin(); it != value.end(); ++it) {
            int u = it->first.first, v = it->first.second, c = it->second;
            g[u].push_back({v, c});
            g[v].push_back({u, c});
        }
        vector<int> dis(n, 0x3f3f3f3f);
        dis[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.emplace(0, 0);
        while (!q.empty()) {
            int d = q.top().first, u = q.top().second;
            q.pop();
            if (dis[u] != d) continue;
            for (pair<int, int>& p : g[u]) {
                int v = p.first, c = p.second;
                if (d + c < disappear[v] && dis[v] > d + c) {
                    dis[v] = d + c;
                    q.emplace(dis[v], v);
                }
            }
        }
        for (int& v : dis)
            if (v == 0x3f3f3f3f) v = -1;
        return dis;
    }
};