class Solution {
public:
    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        vector<int> g[n];

        for (auto& e : roads) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        int m = targetPath.size(), dp[m + 1][n], pre[m + 1][n];
        memset(dp, 0x3f, sizeof(dp));
        memset(pre, -1, sizeof(pre));
        memset(dp[0], 0, sizeof(dp[0]));

        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < n; ++j) {
                int cost = (names[j] == targetPath[i - 1] ? 0 : 1);
                for (int& v : g[j]) {
                    if (dp[i - 1][v] + cost < dp[i][j]) {
                        dp[i][j] = dp[i - 1][v] + cost;
                        pre[i][j] = v;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i < n; ++i)
            if (dp[m][i] < dp[m][ans]) ans = i;
        vector<int> path;
        int cur = ans, x = m;
        while (cur != -1 && x > 0) {
            path.push_back(cur);
            cur = pre[x][cur];
            --x;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};