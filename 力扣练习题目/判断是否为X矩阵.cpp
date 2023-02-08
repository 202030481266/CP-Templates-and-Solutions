class Solution {
public:
    bool checkXMatrix(vector<vector<int>>& grid) {
        int n = grid.size(), cnt = 0;
        for (int i = 0; i < n - 1; ++i)
            if (!grid[i][i] || !grid[i][n - i - 1]) return false;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) 
                if (grid[i][j]) ++cnt;
        return cnt == (2 * n - (n & 1));
    }
};