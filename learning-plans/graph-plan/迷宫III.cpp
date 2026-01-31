class Solution {
    using pii = pair<int, int>;
    static constexpr int dirs[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {

        // init
        int n = maze.size(), m = maze[0].size(), dis[n][m], vis[n][m];
        vector path(n, vector<string>(m));
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        vector<int> g[n * m];
        vector<string> ind{"d", "l", "r", "u"};

        // dijkstra
        dis[ball[0]][ball[1]] = 0;
        vis[ball[0]][ball[1]] = 1;
        priority_queue<pii, vector<pii>, greater<pii>> q;
        q.emplace(0, ball[0] * m + ball[1]);
        while (!q.empty()) {
            int c = q.top().first, x = q.top().second / m, y = q.top().second % m;
            q.pop();
            vis[x][y] = 0;
            for (int i = 0; i < 4; ++i) {
                int nx = x, ny = y, cost = 0;
                while (nx + dirs[i][0] >= 0 && nx + dirs[i][0] < n && ny + dirs[i][1] >= 0 && ny + dirs[i][1] < m && !maze[nx + dirs[i][0]][ny + dirs[i][1]]) {
                    nx += dirs[i][0];
                    ny += dirs[i][1];
                    ++cost;
                    if (nx == hole[0] && ny == hole[1]) { // can't move forward
                        break;
                    }
                }
                if (cost > 0 && dis[nx][ny] > c + cost) {
                    dis[nx][ny] = c + cost;
                    path[nx][ny] = path[x][y] + ind[i];
                    if (!vis[nx][ny]) {
                        vis[nx][ny] = 1;
                        q.emplace(dis[nx][ny], nx * m + ny);
                    }
                }
                else if (cost > 0 && dis[nx][ny] == c + cost && path[nx][ny] > path[x][y] + ind[i]) {
                    path[nx][ny] = path[x][y] + ind[i];
                    if (!vis[nx][ny]) {
                        vis[nx][ny] = 1;
                        q.emplace(dis[nx][ny], nx * m + ny);
                    }
                }
            }
        }

        // find path
        if (dis[hole[0]][hole[1]] == 0x3f3f3f3f) return "impossible";
        return path[hole[0]][hole[1]];
    }
};