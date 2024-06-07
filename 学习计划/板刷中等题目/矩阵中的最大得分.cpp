#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

const int inf = 0x3f3f3f3f;

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), mn[n+1][m+1];
        memset(mn, 0x3f, sizeof(mn));
        int ans = -inf;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int t = min(mn[i-1][j], mn[i][j-1]);
                ans = max(ans, grid[i-1][j-1] - t);
                mn[i][j] = min(grid[i-1][j-1], t);
            }
        }
        return ans;
    }
};