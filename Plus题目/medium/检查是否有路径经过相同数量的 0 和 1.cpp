#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int dp[105][105][105];

class Solution {
public:
    bool isThereAPath(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        if ((n+m-1)%2) return false;
        memset(dp, 0, sizeof(dp));
        int limit = (n+m-1) / 2; // 这是一个定值
        dp[0][1][0] = dp[1][0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                // [1,1] -> [i, j] , 最多就是 (i-1)+(j-1)+1 个 数字
                for (int k = 0; k <= min(i + j - 1, limit); ++k) {
                    if (grid[i-1][j-1]) {
                        if (k > 0)
                            dp[i][j][k] = dp[i-1][j][k-1] | dp[i][j-1][k-1];
                    }
                    else {
                        dp[i][j][k] = dp[i-1][j][k] | dp[i][j-1][k];
                    }
                }
            }
        }
        return dp[n][m][limit];
    }
};