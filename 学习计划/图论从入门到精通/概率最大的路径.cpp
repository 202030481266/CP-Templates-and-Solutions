class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        // 最长路
        priority_queue<pair<double, int>> q;
        vector<pair<int, double>> g[n];
        vector<double> dis(n, 0);
        int N = edges.size();
        for (int i = 0; i < N; ++i) {
            int x = edges[i][0], y = edges[i][1];
            double c = succProb[i];
            g[x].emplace_back(y, c);
            g[y].emplace_back(x, c);
        }
        q.emplace(1.0, start_node);
        dis[start_node] = 1.0;
        while (!q.empty()) {
            auto [prob, u] = q.top();
            q.pop();
            if (prob < dis[u]) continue;
            for (pair<int, double>& p : g[u]) {
                int v = p.first;
                double cost = p.second;
                if (dis[v] < prob * cost) {
                    dis[v] = prob * cost;
                    q.emplace(dis[v], v);
                }
            }
        }
        return dis[end_node];
    }
};