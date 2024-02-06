// 简单的bfs状态规划
class Solution {
    using pii = pair<int, int>;
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = flights.size(), k = days[0].size();
        vector dp(n, vector<int>(k + 1, -1));
        vector vis(n, vector<bool>(k + 1, false));
        dp[0][0] = 0;
        queue<pii> q;
        q.emplace(0, 0);
        vis[0][0] = true;
        while (!q.empty()) {
            auto [u, c] = q.front();
            q.pop();
            vis[u][c] = false;
            if (c == k) continue;
            for (int i = 0; i < n; ++i) {
                if (flights[u][i] || i == u) {
                    if (dp[i][c + 1] < dp[u][c] + days[i][c]) {
                        dp[i][c + 1] = dp[u][c] + days[i][c];
                        if (!vis[i][c + 1]) {
                            vis[i][c + 1] = true;
                            q.emplace(i, c + 1);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) ans = max(ans, dp[i][k]);
        return ans;
    }
};