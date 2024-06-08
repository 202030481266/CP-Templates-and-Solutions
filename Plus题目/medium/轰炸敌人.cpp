#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector rows(2, vector<int>(m+2, 0));
        vector cols(m, vector(2, vector<int>(n+2, 0)));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[j][i] == 'W') cols[i][0][j+1] = 0;
                else cols[i][0][j+1] = cols[i][0][j] + (grid[j][i] == 'E');
            }
            for (int j = n; j >= 1; --j) {
                if (grid[j-1][i] == 'W') cols[i][1][j] = 0;
                else cols[i][1][j] = cols[i][1][j+1] + (grid[j-1][i] == 'E');
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'W') rows[0][j+1] = 0;
                else rows[0][j+1] = rows[0][j] + (grid[i][j] == 'E');
            }
            for (int j = m; j >= 1; --j) {
                if (grid[i][j-1] == 'W') rows[1][j] = 0;
                else rows[1][j] = rows[1][j+1] + (grid[i][j-1] == 'E');
            }
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '0') ans = max(ans, rows[0][j+1] + rows[1][j+1] + cols[j][0][i+1] + cols[j][1][i+1]);
            }
        }
        return ans;
    }
};