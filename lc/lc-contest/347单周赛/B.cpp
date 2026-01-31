class Solution {
public:
    vector<int> cal(vector<int>& c) {
        int n = c.size();
        vector<int> ans(n);
        ans[n - 1] = 0;
        set<int> s;
        s.emplace(c[n - 1]);
        for (int i = n - 2; i >= 0; --i) {
            ans[i] = s.size();
            s.emplace(c[i]);
        }
        return ans;
    }
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), vis[n][m], a[n][m], b[n][m];
        memset(vis, 0, sizeof(vis));
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        // 先计算a
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (vis[i][j]) continue;
                int x = i, y = j;
                vector<int> tmp;
                for (int k = 0; x + k < n && y + k < m; ++k) {
                    vis[x + k][y + k] = 1;
                    tmp.emplace_back(grid[x + k][y + k]);
                }
                auto res = cal(tmp);
                for (int k = 0; k < tmp.size(); ++k) {
                    a[x + k][y + k] = res[k];
                }
            }
        // 计算b
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (vis[i][j]) continue;
                int x = i, y = j;
                vector<int> tmp;
                for (int k = 0; x - k >= 0 && y - k >= 0; ++k) {
                    vis[x - k][y - k] = 1;
                    tmp.emplace_back(grid[x - k][y - k]);
                }
                auto res = cal(tmp);
                for (int k = 0; k < tmp.size(); ++k) {
                    b[x - k][y - k] = res[k];
                }
            }
        vector ans(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans[i][j] = abs(b[i][j] - a[i][j]);
        return ans;
    }
};