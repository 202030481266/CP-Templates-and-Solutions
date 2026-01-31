class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int H, int W) {
        int n = grid.size(), m = grid[0].size();
        int vis[n][m], sum[n + 1][m + 1];
        memset(vis, 0, sizeof(vis));
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) 
                sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + grid[i - 1][j - 1];
        auto f = [&](int x1, int y1, int x2, int y2) -> int {
            ++x1, ++y1, ++x2, ++y2;
            return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
        };
        auto sol = [&](int x1, int y1, int x2, int y2) {
            for (int x = x1; x <= x2; ++x)
                for (int y = y1; y <= y2; ++y) vis[x][y] = 1;
        };
        // 尝试第一遍铺道路
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] || vis[i][j]) continue;
                if (i + H > n || j + W > m) continue; 
                int flag = f(i, j, i + H - 1, j + W - 1);
                if (!flag) sol(i, j, i + H - 1, j + W - 1); 
            }
        }
        // 第二遍
        for (int i = n - 1; i >= 0; --i)
            for (int j = m - 1; j >= 0; --j) {
                if (grid[i][j] || vis[i][j]) continue;
                // i - H + 1, j - W + 1
                if (i - H + 1 < 0 || j - W + 1 < 0) continue;
                int flag = f(i - H + 1, j - W + 1, i, j);
                if (!flag) sol(i - H + 1, j - W + 1, i, j);
            }
        // 第三遍
        for (int i = 0; i < n; ++i)
            for (int j = m - 1; j >= 0; --j) {
                if (grid[i][j] || vis[i][j]) continue;
                if (i + H - 1 >= n || j - W + 1 < 0) continue;
                int flag = f(i, j - W + 1, i + H - 1, j);
                if (!flag) sol(i, j - W + 1, i + H - 1, j);
            }
        // 第四遍
        for (int i = n - 1; i >= 0; --i)
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] || vis[i][j]) continue;
                if (i - H + 1 < 0 || j + W - 1 >= m) continue;
                int flag = f(i - H + 1, j, i, j + W - 1);
                if (!flag) sol(i - H + 1, j, i, j + W - 1);
            }
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j)
                if (!grid[i][j] && !vis[i][j]) return false;
        return true;
    }
};