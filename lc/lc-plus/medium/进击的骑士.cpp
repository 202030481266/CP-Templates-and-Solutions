#include <bits/stdc++.h>
using namespace std;

const int M = 300, N = 620;
int dis[620][620], flag = 0;
class Solution {
public:
    int minKnightMoves(int x, int y) {
        if (!flag) {
            memset(dis, 0x3f, sizeof(dis));
            dis[M][M] = 0;
            queue<pair<int, int>> q;
            q.emplace(M, M);
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (int i = -2; i <= 2; i++) {
                    for (int j = -2; j <= 2; j++) {
                        if (i && j && abs(i) + abs(j) == 3) {
                            int nx = x + i, ny = y + j;
                            if (nx >= 0 && nx < N && ny >= 0 && ny < N && dis[nx][ny] > dis[x][y] + 1) {
                                dis[nx][ny] = dis[x][y] + 1;
                                q.emplace(nx, ny);
                            }
                        }
                    }
                }
            }
            flag = 1;
        }
        x += M, y += M;
        return dis[x][y];
    }
};
