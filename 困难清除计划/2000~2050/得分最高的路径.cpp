class Solution {
public:
    int maximumMinimumPath(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        // dp[x][y] = min(max(dp[x - 1][y], dp[x][y - 1], dp[x + 1][y], dp[x][y + 1]), grid[x][y])

        priority_queue<pair<int, int>> q;
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        vector<vector<int>> dis(n, vector<int>(m));

        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        q.emplace(grid[0][0], 0);
        dis[0][0] = grid[0][0];
        vis[0][0] = true;
        while (!q.empty()) {
            int x = q.top().second / m, y = q.top().second % m, d = q.top().first;
            q.pop();
            vis[x][y] = false;
            if (dis[x][y] != d) continue;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                    if (dis[nx][ny] < min(d, grid[nx][ny])) {
                        dis[nx][ny] = min(d, grid[nx][ny]);
                        if (!vis[nx][ny]) {
                            vis[nx][ny] = true;
                            q.emplace(dis[nx][ny], nx * m + ny);
                        }
                    }
                }
            }
        }
        return dis[n - 1][m - 1];
    }
};