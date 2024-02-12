class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), vis[n][m];
        memset(vis, 0, sizeof(vis));

        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        function<void(int, int)> dfs = [&](int x, int y) {
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] && !vis[nx][ny]) {
                    vis[nx][ny] = 1;
                    dfs(nx, ny);
                }
            }
        };
        for (int i = 0; i < n; ++i) {
            if (grid[i][0] && !vis[i][0]) {
                vis[i][0] = 1;
                dfs(i, 0);
            }
            if (grid[i][m - 1] && !vis[i][m - 1]) {
                vis[i][m - 1] = 1;
                dfs(i, m - 1);
            }
        }
        for (int i = 0; i < m; ++i) {
            if (grid[0][i] && !vis[0][i]) {
                vis[0][i] = 1;
                dfs(0, i);
            }
            if (grid[n - 1][i] && !vis[n - 1][i]) {
                vis[n - 1][i] = 1;
                dfs(n - 1, i);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] && !vis[i][j]) ++ans;
            }
        }
        return ans;
    }
};