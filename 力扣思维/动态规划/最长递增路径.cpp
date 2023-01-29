// https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/
// 技巧：记忆化搜索即可，对于一个固定的点来说，从该点出发的最长递增路径是固定的

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int ans = 1;
        int n = matrix.size(), m = matrix[0].size();
        array<int, 4> dx{-1, 1, 0, 0};
        array<int, 4> dy{0, 0, -1, 1};
        vector<vector<int>> dp(n, vector<int>(m, 0));
        // seems there is no need for vis array
        function<int(int,int)> dfs = [&](int x,int y) -> int {
            if (dp[x][y]) return dp[x][y];
            int len = 0;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if (matrix[nx][ny] > matrix[x][y]) {
                    len = max(len, dfs(nx, ny));
                }
            }
            return dp[x][y] = (1 + len);
        };
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // int temp = dfs(i, j);
                // cout << temp << ' ';
                ans = max(ans, dfs(i, j));
            }
            // cout << '\n';
        }
        return ans;
    }
};