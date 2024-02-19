class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int x = n - 1, y = 0, ans = 0;
        while (y < m) {
            while (x >= 0 && grid[x][y] < 0) {
                --x;
            }
            // (x, n - 1]
            ans += (n - 1 - x);
            ++y;
        }
        return ans;
    }
};