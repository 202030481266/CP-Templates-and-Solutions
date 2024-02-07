class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int n = maze.size(), m = maze[0].size(), dp[n][m];
        memset(dp, 0x3f, sizeof(dp));
        dp[entrance[0]][entrance[1]] = 0;
        queue<pair<int, int>> q;
        q.emplace(entrance[0], entrance[1]);

        int ans = INT_MAX;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if ((x == 0 || y == 0 || x == n - 1 || y == m - 1) && (x != entrance[0] || y != entrance[1])) {
                ans = min(ans, dp[x][y]);
            }
            else {
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i][0], ny = y + dirs[i][1];
                    if (nx >= 0 && ny >= 0 && nx < n && ny < m && maze[nx][ny] == '.') {
                        if (dp[nx][ny] > dp[x][y] + 1) {
                            dp[nx][ny] = dp[x][y] + 1;
                            q.emplace(nx, ny);
                        }
                    }
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};