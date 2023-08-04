class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int dp[(1 << 20)][21];
    int obs[30][30], end, st, n, m, final;
public:
    int dfs(int cur, int s) {
        int& res = dp[s][cur];
        if (res != -1) return res;
        res = 0;
        if (cur == end) return res = (s == final ? 1 : 0);
        int x = cur / m, y = cur % m;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0], ny = y + dirs[i][1], idx = nx * m + ny;
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || obs[nx][ny] || ((s >> idx) & 1)) continue;
            res += dfs(idx, s | (1 << idx));
        }
        return res;
    }
    int uniquePathsIII(vector<vector<int>>& grid) {
        // hamiltion path question
        n = grid.size(), m = grid[0].size();
        int s = 0, ed = 0;
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == -1) {
                    obs[i][j] = 1;
                    continue;
                }
                if (grid[i][j] == 1) st = i * m + j;
                if (grid[i][j] == 2) end = i * m + j;
                final |= (1 << (i * m + j));
            }
        }
        int ans = dfs(st, 1 << st);
        return ans;
    }
};