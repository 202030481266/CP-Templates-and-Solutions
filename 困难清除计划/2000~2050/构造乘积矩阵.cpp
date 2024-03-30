const int mod = 12345;
class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector row(n + 1, vector<int>(m + 1, 1));
        vector rrow(n + 1, vector<int>(m + 2, 1));
        vector<int> sum(n + 1, 1);
        vector<int> suf(n + 2, 1);
        for (int i = 1; i <= n; ++i) { 
            for (int j = 1; j <= m; ++j) 
                row[i][j] = (grid[i - 1][j - 1] % mod * row[i][j - 1]) % mod;
            for (int j = m; j >= 1; --j)
                rrow[i][j] = (grid[i - 1][j - 1] % mod * rrow[i][j + 1]) % mod;
        }
        for (int i = 1; i <= n; ++i)
            sum[i] = (row[i][m] * sum[i - 1]) % mod;
        for (int i = n; i >= 1; --i)
            suf[i] = (row[i][m] * suf[i + 1]) % mod;
        vector ans(n, vector<int>(m, 1));
        for (int i = 1; i <= n; ++i) 
            for (int j = 1; j <= m; ++j)
                ans[i - 1][j - 1] = ((suf[i + 1] * sum[i - 1]) % mod * row[i][j - 1] % mod * rrow[i][j + 1] % mod) % mod;
        return ans;
    }
};