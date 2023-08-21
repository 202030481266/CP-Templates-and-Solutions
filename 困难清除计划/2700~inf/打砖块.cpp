typedef pair<int, int> pii;
class Solution {
    bool del[210][210];
    bool vis[210][210];
    static constexpr int dirs[][4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int n = grid.size(), m = grid[0].size();
        for (auto& h : hits) 
            del[h[0]][h[1]] = true;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) if (!grid[i][j]) vis[i][j] = true;
        queue<pii> q;
        int cur = 0;  // 当前稳定的块
        auto diffusion = [&](int x, int y) {
            queue<pii> q;
            q.emplace(x, y);
            vis[x][y] = true;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                ++cur;
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i][0], ny = y + dirs[i][1];
                    if (nx >= 0 && ny >= 0 && nx < n && ny < m && !vis[nx][ny] && !del[nx][ny] && grid[nx][ny]) {
                        vis[nx][ny] = true;
                        q.emplace(nx, ny);
                    }
                }
            }
        };
        for (int i = 0; i < m; ++i)
            if (!vis[0][i] && !del[0][i]) diffusion(0, i);
        vector<int> ans;
        int tot;
        for (int i = hits.size() - 1; i >= 0; --i) {
            del[hits[i][0]][hits[i][1]] = false;
            if (grid[hits[i][0]][hits[i][1]] == 0) {
                ans.push_back(0);
                continue;
            }
            bool flag = (hits[i][0] == 0);
            tot = cur;
            if (!flag) {
                for (int j = 0; j < 4; ++j) {
                    int nx = hits[i][0] + dirs[j][0], ny = hits[i][1] + dirs[j][1];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m || !vis[nx][ny] || del[nx][ny] || !grid[nx][ny]) continue;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                diffusion(hits[i][0], hits[i][1]);
                ans.push_back(cur - tot - 1);
            }
            else ans.push_back(0);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};