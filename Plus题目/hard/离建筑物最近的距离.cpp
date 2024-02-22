class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int shortestDistance(vector<vector<int>>& grid) {
        vector<int> a, b;
        int n = grid.size(), m = grid[0].size(), dis[n][m], vis[n][m];
        // O((n*m)^2) 
        memset(dis, 0, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        int time = 0;
        auto f = [&](int x, int y) {
            vector<pair<int, int>> q;
            q.emplace_back(x, y);
            for (int d = 0; !q.empty(); ++d) {
                vector<pair<int, int>> tmp;
                for (pair<int,int>& p : q) {
                    int x = p.first, y = p.second;
                    dis[x][y] += d;
                    for (int i = 0; i < 4; ++i) {
                        int nx = x + dirs[i][0], ny = y + dirs[i][1];
                        if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0 && vis[nx][ny] == time) {
                            ++vis[nx][ny];
                            tmp.emplace_back(nx, ny);
                        }
                    }
                }
                q = move(tmp);
            }
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    f(i, j);
                    ++time;
                }
            }
        }
        int ans = INT_MAX;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] == 0 && vis[i][j] == time)
                    ans = min(ans, dis[i][j]);
        return ans == INT_MAX ? -1 : ans;
    }
};