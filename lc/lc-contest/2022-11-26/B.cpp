class Solution {
public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> row(n + 1, vector<int>(2)); 
        vector<vector<int>> col(m + 1, vector<int>(2));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                row[i][1] += (grid[i][j] == 1);
                row[i][0] += (grid[i][j] == 0);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                col[i][1] += (grid[j][i] == 1);
                col[i][0] += (grid[j][i] == 0);
            }
        }
        vector<vector<int>> ans(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i][j] = row[i][1] + col[j][1] - row[i][0] - col[j][0];
            }
        }
        return ans;
    }
};