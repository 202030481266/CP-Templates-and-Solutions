class Solution {
public:
    int minimumSeconds(vector<vector<string>>& land) {
        int n = land.size(), m = land[0].size();

        const int inf = 0x3f3f3f3f;
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        vector<vector<int>> dis(n, vector<int>(m, inf));
        vector<vector<int>> d(n, vector<int>(m, inf));
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        int ed_x, ed_y, st_x, st_y;
        queue<pair<int, int>> q;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (land[i][j] == "D") {
                    ed_x = i;
                    ed_y = j;
                } else if (land[i][j] == "S") {
                    st_x = i;
                    st_y = j;
                } 
                else if (land[i][j] == "*") {
                    d[i][j] = 0;
                    q.emplace(i, j);
                    vis[i][j] = true;
                }
            }
        }
        while (!q.empty()) {
            int x = q.front().first, y = q.front().second;
            q.pop();
            vis[x][y] = false;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                    land[nx][ny] != "X" && land[nx][ny] != "D") {
                    if (d[nx][ny] > d[x][y] + 1) {
                        d[nx][ny] = d[x][y] + 1;
                        if (!vis[nx][ny]) {
                            vis[nx][ny] = true;
                            q.emplace(nx, ny);
                        }
                    }
                }
            }
        }
        dis[st_x][st_y] = 0;
        q.emplace(st_x, st_y);
        vis[st_x][st_y] = true;
        while (!q.empty()) {
            int x = q.front().first, y = q.front().second;
            q.pop();
            vis[x][y] = false;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                    land[nx][ny] != "X" ) {
                    if (d[nx][ny] > dis[x][y] + 1 &&
                        dis[nx][ny] > dis[x][y] + 1) {
                        dis[nx][ny] = dis[x][y] + 1;
                        if (!vis[nx][ny]) {
                            vis[nx][ny] = true;
                            q.emplace(nx, ny);
                        }
                    }
                }
            }
        }
        // debug
        // for (int i = 0; i < n;++i) {
        //     for (int j = 0; j < m; ++j) cout << land[i][j];
        //     cout << endl;
        // }
        // cout << "------------------------------" << endl;
        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < m; ++j) cout << (dis[i][j] == inf ? "inf" : to_string(dis[i][j])) << '\t';
        //     cout << endl;
        // }
        return dis[ed_x][ed_y] == inf ? -1 : dis[ed_x][ed_y];
    }
};