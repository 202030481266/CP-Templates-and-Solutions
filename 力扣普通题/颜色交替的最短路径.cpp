class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<int> rg[n], bg[n];
        for (auto c : redEdges) rg[c[0]].emplace_back(c[1]);
        for (auto c : blueEdges) bg[c[0]].emplace_back(c[1]);
        vector<int> dis1(n, INT_MAX), dis2(n, INT_MAX), dis(n, -1);

        queue<pair<int,int>> q;
        q.emplace(0, 0);
        q.emplace(0, 1);
        dis1[0] = dis2[0] = dis[0] = 0;
        int cur = 0;
        // 0 is red , 1 is blue
        // dis1[v] is red road to v 
        // dis2[v] is blue road to v
        auto addred = [&](int u) {
            for (auto v : rg[u])
                if (dis1[v] == INT_MAX) {
                    dis1[v] = dis2[u] + 1;
                    q.emplace(v, 1);
                }
        };
        auto addblue = [&](int u) {
            for (auto v : bg[u]) 
                if (dis2[v] == INT_MAX) {
                    dis2[v] = dis1[u] + 1;
                    q.emplace(v, 0);
                }
        };
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            if (u.second == 0) {
                addred(u.first);
            } else {
                addblue(u.first);
            }
        }
        for (int i = 0; i < n; ++i) {
            int temp = min(dis1[i], dis2[i]);
            dis[i] = (temp == INT_MAX ? -1 : temp);
        }
        return dis;
    }
};