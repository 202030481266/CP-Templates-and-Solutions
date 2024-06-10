#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct node {
    int x,y,d;
};

class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int n = maze.size(), m = maze[0].size(), vis[n][m][5];
        memset(vis, 0, sizeof(vis));
        queue<node> q;
        vis[start[0]][start[1]][4] = 1;
        q.push({start[0], start[1], 4});// 停止状态
        while (!q.empty()) {
            node u = q.front();
            q.pop();
            int x = u.x, y = u.y, d = u.d;
            if (d == 4) {
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i][0], ny = y + dirs[i][1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] == 0 && !vis[nx][ny][i]) {
                        vis[nx][ny][i] = 1;
                        q.push({nx, ny, i});
                    }
                }
            }
            else {
                int nx = x + dirs[d][0], ny = y + dirs[d][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) { // 迷宫里面
                    if (maze[nx][ny] == 0) { // 继续前进
                        if (!vis[nx][ny][d]) {
                            vis[nx][ny][d] = 1;
                            q.push({nx, ny, d});
                        }
                    }
                    else {// 停止
                        if (!vis[x][y][4]) {
                            vis[x][y][4] = 1;
                            q.push({x, y, 4});
                        }
                    }
                }
                else { // 出界
                    if (!vis[x][y][4]) {
                        vis[x][y][4] = 1;
                        q.push({x, y, 4});
                    }
                }
            }
        }
        return vis[destination[0]][destination[1]][4];
    }
};