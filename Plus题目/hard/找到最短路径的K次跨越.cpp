struct node {
    int id, cnt, dis;
    node(int _id, int _cnt, int _dis): id(_id), cnt(_cnt), dis(_dis) {}
    bool operator < (const node& rhs) const {
        return dis < rhs.dis;
    }
    bool operator > (const node& rhs) const {
        return dis > rhs.dis;
    }
};
class Solution {
public:
    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {
        // 最短路
        int dp[n][k + 1];
        memset(dp, 0x3f, sizeof(dp));

        vector<pair<int, int>> g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back({v, e[2]});
            g[v].push_back({u, e[2]});
        }

        priority_queue<node, vector<node>, greater<node>> q;
        q.push(node(s, k, 0));
        dp[s][k] = 0;
        while (!q.empty()) {
            node cur = q.top();
            q.pop();
            if (dp[cur.id][cur.cnt] != cur.dis) continue;
            for (pair<int, int>& p : g[cur.id]) {
                int v = p.first, c = p.second;
                if (cur.cnt > 0 && dp[v][cur.cnt - 1] > cur.dis) {
                    dp[v][cur.cnt - 1] = cur.dis;
                    q.push(node(v, cur.cnt - 1, cur.dis));
                }
                if (dp[v][cur.cnt] > cur.dis + c) {
                    dp[v][cur.cnt] = cur.dis + c;
                    q.push(node(v, cur.cnt, cur.dis + c));
                }
            }
        }

        int ans = 0x3f3f3f3f;
        for (int i = 0; i <= k; ++i)
            ans = min(ans, dp[d][i]);
        return ans;
    }
};