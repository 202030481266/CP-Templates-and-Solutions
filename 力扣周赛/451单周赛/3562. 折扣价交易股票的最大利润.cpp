static constexpr int N = 161;

int dp[N][N*2][2];

class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector g(n, vector<int>());
        for (auto& e : hierarchy) {
            int u = e[0] - 1, v = e[1] - 1;
            g[u].push_back(v);
        }
        int vol = budget + 25;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= vol; ++j) dp[i][j][0] = dp[i][j][1] = 0;
        }
        auto dfs = [&](auto&& dfs_ref,int u) -> void {
            for (int v : g[u]) {
                dfs_ref(dfs_ref, v);
                for (int i = vol; i >= 1; --i) {
                    for (int x = 1; x <= i; ++x) {
                        dp[u][i][0] = max(dp[u][i][0], dp[u][i - x][0] +
                            max(dp[v][x][0], dp[v][x][1]));
                    }
                }
                for (int i = vol; i >= present[u]; --i) {
                    for (int x = 0; x <= i - present[u]; ++x) {
                        int tmp = (present[v] + 1) / 2;
                        dp[u][i][1] = max(dp[u][i][1], dp[u][i - x][1] + dp[v][x][0]);
                        if (x >= present[v] / 2) 
                            dp[u][i][1] = max(dp[u][i][1], dp[u][i - x][1] + dp[v][x + tmp][1] + tmp);
                    }
                }
            }
            for (int i = vol; i >= present[u]; --i) dp[u][i][1] += future[u] - present[u];
            };
        dfs(dfs, 0);
        int ans = 0;
        for (int i = 1; i <= budget; ++i) ans = max(ans, max(dp[0][i][0], dp[0][i][1]));
        return ans;
    }
};
