// https://leetcode.cn/problems/snakes-and-ladders/
// 有一次非常深刻地理解了BFS的原理，这道题的关键在于传送的落地点并不是v而是g[v], 所以更新的是g[v]而不是v


class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();

        auto encode = [&](int x, int y) {
            if (n & 1) return (x & 1) ? (n * (n - x) - y) : (n * (n - x) - (n - 1) + y);
            return (x & 1) ? (n * (n - x) - (n - 1) + y) : (n * (n - x) - y);
        };

        // flatten
        vector<int> g(n * n + 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int t = encode(i, j);
                g[t] = board[i][j];
            }

        vector<int> dis(n * n + 1, 0x3f3f3f3f);
        vector<bool> vis(n * n + 1, false);
        dis[1] = 0;
        vis[1] = true;
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == n * n) return dis[n * n];
            for (int v = u + 1; v <= min(n * n, u + 6); ++v) {
                if (g[v] == -1 && !vis[v]) {
                    dis[v] = min(dis[v], dis[u] + 1);
                    vis[v] = true;
                    q.push(v);
                } else if (g[v] > 0 && !vis[g[v]]) {
                    // will be at g[v] but not v
                    dis[g[v]] = min(dis[g[v]], dis[u] + 1);
                    vis[g[v]] = true;
                    q.push(g[v]);
                }
            }
        }
        return -1;
    }

};