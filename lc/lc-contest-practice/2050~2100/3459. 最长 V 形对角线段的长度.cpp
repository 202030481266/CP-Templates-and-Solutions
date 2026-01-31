#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int dirs[4][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), dp[4][n][m];
        memset(dp, 0, sizeof dp);

        auto sol = [&](int dir, int x, int y) {
            int r = (dir + 2) % 4;
            int dx = dirs[r][0], dy = dirs[r][1];
            dp[dir][x][y] = 1;
            while (x + dx >= 0 && y + dy >= 0 && x + dx < n && y + dy < m) {
                dp[dir][x+dx][y+dy] = 1;
                if (grid[x+dx][y+dy] == 1) {
                    if (grid[x][y] == 2) dp[dir][x+dx][y+dy] = dp[dir][x][y] + 1;
                }
                else if (grid[x+dx][y+dy] == 0) {
                    if (grid[x][y] == 2) dp[dir][x+dx][y+dy] = dp[dir][x][y] + 1;
                }
                else {
                    if (grid[x][y] == 0) dp[dir][x+dx][y+dy] = dp[dir][x][y] + 1;
                }
                x += dx;
                y += dy; 
            }
        };
        // 第一个方向
        for (int i = 0; i < n; ++i) sol(0, i, 0);
        for (int i = 1; i < m; ++i) sol(0, 0, i);
        // 第二个方向
        for (int i = 0; i < m; ++i) sol(1, 0, i);
        for (int i = 1; i < n; ++i) sol(1, i, m-1);
        // 第三个方向
        for (int i = 0; i < n; ++i) sol(2, i, m-1);
        for (int i = m-2; i >= 0; --i) sol(2, n-1, i);
        // 第四个方向
        for (int i = 0; i < m; ++i) sol(3, n-1, i);
        for (int i = n-2; i >= 0; --i) sol(3, i, 0);
        
        int ans = 0;
        auto f = [&](int dir, int x, int y) {
            int dx = dirs[dir][0], dy = dirs[dir][1];
            while (x >= 0 && y >= 0 && x < n && y < m) {
                if (grid[x][y] == 1) {
                    int tmp = dp[dir][x][y];
                    for (int j = 1; j <= tmp; ++j) {
                        ans = max(ans, j + dp[(dir+1)%4][x][y] - 1);
                        x += dx;
                        y += dy;
                    }
                }
                else {
                    x += dx;
                    y += dy;
                }
            }
        };
        // 第一个方向
        for (int i = 0; i < n; ++i) f(0, i, m-1);
        for (int i = m-2; i >= 0; --i) f(0, n-1, i);
        // 第二个方向
        for (int i = 0; i < m; ++i) f(1, n-1, i);
        for (int i = n-2; i >= 0; --i) f(1, i, 0);
        // 第三个方向
        for (int i = 0; i < n; ++i) f(2, i, 0);
        for (int i = 1; i < m; ++i) f(2, 0, i);
        // 第四个方向
        for (int i = 0; i < m; ++i) f(3, 0, i);
        for (int i = 1; i < n; ++i) f(3, i, m-1);
        return ans;
    }
};