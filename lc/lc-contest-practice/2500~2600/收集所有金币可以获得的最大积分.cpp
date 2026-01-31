class Solution {
public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        int n = coins.size(), dp[n][14], f[n][14];
        memset(dp, -1, sizeof(dp));

        // 建图
        vector<int> g[n];
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        for (int i = 0; i < n; ++i) {
            int x = coins[i];
            for (int j = 0; j < 14; ++j) {
                f[i][j] = x;
                x = x / 2;
            }
        }

        function<int(int,int,int)> dfs = [&](int u, int fa, int cnt) -> int {
            // 在已经有了cnt次的减少下还能获取的最大值
            if (cnt >= 14) return 0;
            if (dp[u][cnt] != -1) return dp[u][cnt];
            int a = f[u][cnt] - k, b = (cnt + 1 < 14 ? f[u][cnt + 1] : 0);
            for (int& v : g[u]) {
                if (v != fa) {
                    a += dfs(v, u, cnt);
                    b += dfs(v, u, cnt + 1);
                }
            }
            return dp[u][cnt] = max(a, b);
        };

        return dfs(0, 0, 0);
    }
};