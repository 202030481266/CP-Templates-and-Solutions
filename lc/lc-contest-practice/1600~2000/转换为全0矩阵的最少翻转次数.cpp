class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int minFlips(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size(), dp[(1 << (m * n))];
        memset(dp, 0x3f, sizeof(dp));

        queue<pair<int, int>> q;
        int ed = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (mat[i][j]) ed |= (1 << (i * m + j));
        q.emplace(0, 0);
        dp[0] = 0;
        while (!q.empty()) {
            auto [u, v] = q.front();
            q.pop();
            // cout << u << ' ' << v << endl;
            if (u == ed) return v;
            for (int i = 0; i < n * m; ++i) {
                // 枚举翻转的点
                int x = i / m, y = i % m, nxt = u ^ (1 << i);
                for (int k = 0; k < 4; ++k) {
                    int nx = x + dirs[k][0], ny = y + dirs[k][1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                        nxt ^= (1 << (nx * m + ny));
                    }
                }
                if (dp[nxt] == 0x3f3f3f3f) {
                    dp[nxt] = v + 1;
                    q.emplace(nxt, v + 1);
                }
            }
        }
        return -1;
    }
};