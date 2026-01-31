#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        // dis[i][j][s] = min(max(t[i][j], dis[x][y])+c)
        // 两个最短路的组合
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> q;
        int n = moveTime.size(), m = moveTime[0].size(), dis[n][m];
        memset(dis, 0x3f, sizeof(dis));
        dis[0][0] = 0;
        q.push({0,1,0});
        while (!q.empty()) {
            auto [d, c, id] = q.top();
            q.pop();
            int x = id / m, y = id % m;
            if (d != dis[x][y]) continue;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if (dis[nx][ny] > max(d,moveTime[nx][ny]) + c) {
                    dis[nx][ny] = max(d, moveTime[nx][ny]) + c;
                    q.emplace(dis[nx][ny], (c == 1 ? 2 : 1), nx * m + ny);
                }
            }
        }
        return dis[n-1][m-1];
    }
};