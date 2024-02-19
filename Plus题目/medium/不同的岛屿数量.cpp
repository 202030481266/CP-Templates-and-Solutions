class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        // 找到所有的连通块然后逐个比较
        int n = grid.size(), m = grid[0].size();
        vector<vector<pair<int, int>>> g;
        vector<pair<int, int>> cur;
        vector vis(n, vector<bool>(m, false));
        
        function<void(int,int)> dfs = [&](int x, int y) {
            cur.emplace_back(x, y);
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && !vis[nx][ny] && grid[nx][ny]) {
                    vis[nx][ny] = true;
                    dfs(nx, ny);
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!vis[i][j] && grid[i][j]) {
                    vis[i][j] = true;
                    cur = vector<pair<int, int>>{};
                    dfs(i, j);
                    g.push_back(cur);
                }
            }
        }

        for (vector<pair<int, int>>& v : g) 
            sort(v.begin(), v.end());

        int ans = 0;
        for (int i = 0; i < g.size(); ++i) {
            bool flag = true;
            // 按照x轴排序之后
            for (int j = 0; j < i; ++j) {
                // i -> j
                if (g[i].size() != g[j].size()) continue;
                pair<int, int> offset = make_pair(g[j][0].first - g[i][0].first, g[j][0].second - g[i][0].second);
                bool res = true;
                for (int k = 0; k < g[i].size(); ++k) {
                    if (g[i][k].first + offset.first != g[j][k].first || g[i][k].second + offset.second != g[j][k].second) {
                        res = false;
                        break;
                    }
                }
                if (res) {
                    flag = false;
                    break;
                }
            }
            if (flag) ++ans;
        }
        return ans;
    }
};