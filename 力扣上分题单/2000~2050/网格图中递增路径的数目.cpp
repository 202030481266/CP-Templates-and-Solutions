// https://leetcode.cn/problems/number-of-increasing-paths-in-a-grid/



class Solution {
    const int MOD = 1e9 + 7;
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    int countPaths(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        int f[m][n]; memset(f, -1, sizeof(f));
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (f[i][j] != -1) return f[i][j];
            int res = 1;
            for (auto &d : dirs) {
                int x = i + d[0], y = j + d[1];
                if (0 <= x && x < m && 0 <= y && y < n && grid[x][y] > grid[i][j])
                    res = (res + (dfs(x, y))) % MOD;
            }
            return f[i][j] = res;
        };
        int ans = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                ans = (ans + dfs(i, j)) % MOD;
        return ans;
    }
};