class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<vector<int>> g(n);

        vector<int> dis1(n, 0x3f3f3f3f), dis2(n, 0x3f3f3f3f);
        for (int i = 0; i < n; ++i) {
            if (edges[i] != -1) g[i].emplace_back(edges[i]);
        }
        queue<int> q1, q2;

        auto bfs = [&](queue<int>& q, vector<int>& dis, int& st) {
            dis[st] = 0;
            q.emplace(st);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : g[u]) {
                    if (dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        q.emplace(v);
                    }
                }
            }
        };
        bfs(q1, dis1, node1);
        bfs(q2, dis2, node2);
        int ans = 0x3f3f3f3f, res = -1;
        for (int i = 0; i < n; ++i) {
            if (dis1[i] != 0x3f3f3f3f && dis2[i] != 0x3f3f3f3f) {
                if (max(dis1[i], dis2[i]) < ans)
                    ans = max(dis1[i], dis2[i]), res = i;
            }
        }
        return res;
    }
};
