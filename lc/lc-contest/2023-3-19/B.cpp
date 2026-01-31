class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> a(n * n);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                a[grid[i][j]].emplace_back(i);
                a[grid[i][j]].emplace_back(j);
            }

        int x = 0, y = 0, cnt;
        if (a[0][0] == 0 && a[0][1] == 0) {
            cnt = 1;
        }
        else cnt = 0;
        while (cnt < n * n) {
            int nx = a[cnt][0], ny = a[cnt][1];
            if ((abs(nx - x) == 2 && abs(ny - y) == 1) || (abs(nx - x) == 1 && abs(ny - y) == 2)) {
                ++cnt;
                x = nx;
                y = ny;
            } 
            else return false;
        }
        return true;
    }
};