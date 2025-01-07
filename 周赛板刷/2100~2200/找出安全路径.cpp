typedef pair<int,int> pii;
class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size(), dis[n][n];
        memset(dis, 0x3f, sizeof(dis));
        queue<pii> q;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) 
                if (grid[i][j]) {
                    q.emplace(i, j);
                    dis[i][j] = 0;
                }
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if (dis[nx][ny] > dis[x][y] + 1) {
                    dis[nx][ny] = dis[x][y] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        int vis[n][n];
        function<void(int, int, int)> dfs = [&](int x, int y, int v) {
            if (vis[x][y] || dis[x][y] < v) return;
            vis[x][y] = 1;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                dfs(nx, ny, v);
            }
        };
        int l = 0, r = 2 * n, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            memset(vis, 0, sizeof(vis));
            dfs(0, 0, mid);
            if (vis[n - 1][n - 1]) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        assert(ans != -1);
        return ans;
    }
};