class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        auto f = [&](int x, int y) {
            // from (x, y)
            int ans = 0;
            for (int len = 1; x + len - 1 < n && y + len - 1 < m; ++len) {
                bool flag = true;
                for (int i = x; i <= x + len - 1; ++i) 
                    if (!grid[i][y] || !grid[i][y + len - 1]) flag = false;
                for (int i = y; i <= y + len - 1; ++i)
                    if (!grid[x][i] || !grid[x + len - 1][i]) flag = false;
                if (flag) ans = len;
            }
            return ans;
        };
        int res = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (!grid[i][j]) continue;
                int k = f(i, j);
                res = max(res, k * k);
            }
        return res;
    }
};