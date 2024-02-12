class Solution {
    using pii = pair<int, int>;
public:
    void debug(vector<vector<int>>& maze) {
        for (vector<int>& e : maze) {
            for (int j = 0; j < e.size(); ++j) {
                if (e[j]) {
                    cout << '#';
                }
                else cout << '.';
            }
            cout << endl;
        }
    }
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int n = maze.size(), m = maze[0].size(), dis[n][m];
        memset(dis, 0x3f, sizeof(dis));
        // debug(maze);
        dis[start[0]][start[1]] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> q;
        q.emplace(0, start[0] * m + start[1]);
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            int c = q.top().first, x = q.top().second / m, y = q.top().second % m;
            q.pop();
            if (dis[x][y] < c) continue;
            if (x == destination[0] && y == destination[1]) return c;
            for (int i = 0; i < 4; ++i) {
                int nx = x, ny = y, cost = 0;
                while (nx + dirs[i][0] >= 0 && nx + dirs[i][0] < n && ny + dirs[i][1] >= 0 && ny + dirs[i][1] < m && !maze[nx + dirs[i][0]][ny + dirs[i][1]]) {
                    nx += dirs[i][0];
                    ny += dirs[i][1];
                    ++cost;
                }
                if (dis[nx][ny] > dis[x][y] + cost) {
                    dis[nx][ny] = dis[x][y] + cost;
                    q.emplace(dis[nx][ny], nx * m + ny);
                }
            }
        }
        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < m; ++j) {
        //         if (dis[i][j] == 0x3f3f3f3f) cout << '*' << '\t';
        //         else cout << dis[i][j] << '\t';
        //     }
        //     cout << '\n';
        // }
        return -1;
    }
};