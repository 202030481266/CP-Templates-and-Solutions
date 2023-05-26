class Solution {
    static constexpr int dirs[8][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    typedef pair<int, int> pii;
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size(), dis[n][n];
        memset(dis, 0x3f, sizeof(dis));
        if (grid[0][0]) return -1;
        queue<pii> q;
        dis[0][0] = 1;
        q.emplace(0, 0);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 8; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny]) continue;
                if (dis[nx][ny] > dis[x][y] + 1) {
                    dis[nx][ny] = dis[x][y] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        return dis[n - 1][n - 1] == 0x3f3f3f3f ? -1 : dis[n - 1][n - 1];
    }
};