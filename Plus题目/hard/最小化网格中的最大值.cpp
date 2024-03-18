class Solution {
public:
    // 不可能存在环
    vector<vector<int>> minScore(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> row(n), col(m);

        vector<int> tot(n * m);
        iota(tot.begin(), tot.end(), 0);
        sort(tot.begin(), tot.end(), [&](int i, int j) {
            return grid[i / m][i % m] < grid[j / m][j % m];
        });

        for (int& i : tot) {
            int r = i / m, c = i % m;
            grid[r][c] = max(row[r], col[c]) + 1;
            row[r] = col[c] = grid[r][c];
        }
        return grid;
    }
};