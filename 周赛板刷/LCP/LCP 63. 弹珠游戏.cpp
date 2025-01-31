#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 0, 1, 2, 3
// R, D, L, U
const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
public:
    vector<vector<int>> ballGame(int num, vector<string>& plate) {
        int n = plate.size(), m = plate[0].size(), dp[n][m][4];
        memset(dp, 0x3f, sizeof(dp));
        queue<tuple<int,int,int>> q;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (plate[i][j] == 'O') {
                    for (int d = 0; d < 4; ++d) {
                        // 什么方向都可以进去
                        q.push({i, j, d});
                        dp[i][j][d] = 0;
                    }
                }
            }
        }
        while (!q.empty()) {
            auto [x, y, d] = q.front();
            q.pop();
            int dd = d;
            if (plate[x][y] == 'W') {
                dd = (d+1) % 4;
            }
            else if (plate[x][y] == 'E') {
                dd = (d+3) % 4;
            }
            // nx + dd[i][0] = x
            // ny + dd[i][1] = y
            int nx = x - dirs[dd][0], ny = y - dirs[dd][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && dp[nx][ny][dd] > dp[x][y][d]+1) {
                dp[nx][ny][dd] = dp[x][y][d] + 1;
                q.push({nx, ny, dd});
            }
        }
        vector<vector<int>> ans;
        for (int i = 1; i < m-1; ++i) {
            if (dp[0][i][1] <= num && plate[0][i] == '.') {
                ans.push_back({0, i});
            }
            if (dp[n-1][i][3] <= num && plate[n-1][i] == '.') {
                ans.push_back({n-1, i});
            }
        }
        for (int i = 1; i < n-1; ++i) {
            if (dp[i][0][0] <= num && plate[i][0] == '.') {
                ans.push_back({i, 0});
            }
            if (dp[i][m-1][2] <= num && plate[i][m-1] == '.') {
                ans.push_back({i, m-1});
            }
        }
        return ans;
    }
};