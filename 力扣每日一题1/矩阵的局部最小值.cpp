class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n = grid.size();

        vector ans(n - 2, vector<int>(n - 2));

        auto f = [&](int x, int y) {
            int m_1 = max({grid[x][y], grid[x][y + 1], grid[x][y + 2]});
            int m_2 = max({grid[x + 1][y], grid[x + 1][y + 1], grid[x + 1][y + 2]});
            int m_3 = max({grid[x + 2][y], grid[x + 2][y + 1], grid[x + 2][y + 2]});
            return max({m_1, m_2, m_3});
        };

        for (int i = 0; i < n - 2; ++i) 
            for (int j = 0; j < n - 2; ++j) 
                ans[i][j] = f(i, j);
        return ans;
    }
};