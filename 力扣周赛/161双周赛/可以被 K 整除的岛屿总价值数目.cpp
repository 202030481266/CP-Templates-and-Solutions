#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


static constexpr int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        ll cur = 0;
        vector vis(n, vector<bool>(m));
        auto dfs = [&](auto&& self, int x, int y) -> void {
            vis[x][y] = true;
            cur += grid[x][y];
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m || !grid[nx][ny] || vis[nx][ny]) continue;
                self(self, nx, ny);
            }
        };
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] && !vis[i][j]) {
                    cur = 0;
                    dfs(dfs, i, j);
                    if (cur % k == 0) ++ans;
                }
            }
        }
        return ans;
    }
};