// https://leetcode.cn/problems/minimum-time-to-visit-a-cell-in-a-grid/description/
// 方法一就是使用最短路问题，因为可以在一开始就反复横跳直到某一个格子可以通行，
// 		那么距离dis和坐标和奇偶性一定相同，利用这个约束进行最短路更新，非常巧妙!
// 方法二就是单调二分终点的到达时间，然后判断是否能够从终点回到出发点

class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    int minimumTime(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][1] > 1 && grid[1][0] > 1) // 无法「等待」
            return -1;

        int dis[m][n];
        memset(dis, 0x3f, sizeof(dis));
        dis[0][0] = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.emplace(0, 0, 0);
        for (;;) {
            auto[d, i, j] = pq.top();
            pq.pop();
            if (i == m - 1 && j == n - 1)
                return d;
            for (auto &q : dirs) { // 枚举周围四个格子
                int x = i + q[0], y = j + q[1];
                if (0 <= x && x < m && 0 <= y && y < n) {
                    int nd = max(d + 1, grid[x][y]);
                    nd += (nd - x - y) % 2; // nd 必须和 x+y 同奇偶
                    if (nd < dis[x][y]) {
                        dis[x][y] = nd; // 更新最短路
                        pq.emplace(nd, x, y);
                    }
                }
            }
        }
        return 0;
    }
};


// 二分答案 + bfs
class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    int minimumTime(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][1] > 1 && grid[1][0] > 1) // 无法「等待」
            return -1;

        int vis[m][n]; memset(vis, -1, sizeof(vis));
        auto check = [&](int end_time) -> bool {
            vis[m - 1][n - 1] = end_time;
            vector<pair<int, int>> q = {{m - 1, n - 1}};
            for (int t = end_time - 1; !q.empty(); --t) {
                vector<pair<int, int>> nxt;
                for (auto &[i, j] : q) {
                    for (auto &d : dirs) { // 枚举周围四个格子
                        int x = i + d[0], y = j + d[1];
                        if (0 <= x && x < m && 0 <= y && y < n && vis[x][y] != end_time && grid[x][y] <= t) {
                            if (x == 0 && y == 0) return true;
                            vis[x][y] = end_time; // 用二分的值来标记，避免重复创建 vis 数组
                            nxt.emplace_back(x, y);
                        }
                    }
                }
                q = move(nxt);
            }
            return false;
        };

        int left = max(grid.back().back(), m + n - 2) - 1, right = 1e5 + m + n; // 开区间
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right + (right + m + n) % 2;
    }
};

