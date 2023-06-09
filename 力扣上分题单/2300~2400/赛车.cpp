class Solution {
    static constexpr int N = 20010;
    typedef tuple<int, int, int> tiii;
public:
    int racecar(int target) {
        int dis[N][20][2];  // 无论如何速度都不可能超过2^20
        memset(dis, -1, sizeof(dis));
        dis[10000][0][1] = 0;
        queue<tiii> q;
        q.emplace(10000, 0, 1);
        while (!q.empty()) {
            auto [pos, speed, dir] = q.front();
            q.pop();
            if (pos == target + 10000) return dis[pos][speed][dir];
            int x, y;
            if (dir == 0) {
                // x轴负方向
                // A
                x = pos - pow(2, speed);
                y = speed + 1;
                if (x >= 0 && y < 20 && dis[x][y][0] == -1) {
                    dis[x][y][0] = dis[pos][speed][0] + 1;
                    q.emplace(x, y, 0);
                }
                // R
                if (dis[pos][0][1] == -1) {
                    dis[pos][0][1] = dis[pos][speed][0] + 1;
                    q.emplace(pos, 0, 1);
                }
            }
            else {
                // x轴正方向
                // A
                x = pos + pow(2, speed);
                y = speed + 1;
                if (x < N && y < 20 && dis[x][y][1] == -1) {
                    dis[x][y][1] = dis[pos][speed][1] + 1;
                    q.emplace(x, y, 1);
                }
                // R
                if (dis[pos][0][0] == -1) {
                    dis[pos][0][0] = dis[pos][speed][1] + 1;
                    q.emplace(pos, 0, 0);
                }
            }
        }
        return -1;
    }
};