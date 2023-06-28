class Solution {
    typedef pair<int, int> pii;
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size(), w[n][n], dp[n][maxTime + 1];
        memset(w, 0x3f, sizeof(w));
        memset(dp, 0x3f, sizeof(dp));
        vector<int> g[n];
        set<pii> s;
        for (auto& c : edges) {
            w[c[0]][c[1]] = min(w[c[0]][c[1]], c[2]);
            w[c[1]][c[0]] = min(w[c[1]][c[0]], c[2]);
            s.emplace(c[0], c[1]);
            s.emplace(c[1], c[0]);
        }
        for (auto [u, v] : s) g[u].emplace_back(v);
        dp[0][0] = passingFees[0];
        queue<pii> q;
        q.emplace(0, 0);
        while (!q.empty()) {
            auto [u, t] = q.front();
            q.pop();
            for (int v : g[u]) {
                if (t + w[u][v] <= maxTime && dp[v][t + w[u][v]] > dp[u][t] + passingFees[v]) {
                    dp[v][t + w[u][v]] = dp[u][t] + passingFees[v];
                    q.emplace(v, t + w[u][v]);
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for (int i = 1; i <= maxTime; ++i)
            ans = min(ans, dp[n - 1][i]);
        return (ans == 0x3f3f3f3f ? -1 : ans);
    }
};