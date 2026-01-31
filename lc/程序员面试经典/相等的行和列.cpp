class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        unordered_map<string, int> cnt;  
        for (int i = 0; i < n; ++i) {
            string tmp;
            for (int j = 0; j < m; ++j) tmp = tmp + " " + to_string(grid[i][j]);
            ++cnt[tmp];
        }
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            string tmp;
            for (int j = 0; j < n; ++j) tmp = tmp + " " + to_string(grid[j][i]);
            ans += cnt[tmp];
        }
        return ans;
    }
};