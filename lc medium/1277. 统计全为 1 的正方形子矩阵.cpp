#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int dp[301][301], up[301][301], l[301][301];

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        for (int i = 1; i <= n; ++i) {
            l[i][0] = 0;
            for (int j = 1; j <= m; ++j) {
                if (matrix[i-1][j-1]) l[i][j] = l[i][j-1] + 1;
                else l[i][j] = 0;
            }
        }
        for (int j = 1; j <= m; ++j) {
            up[0][j] = 0;
            for (int i = 1; i <= n; ++i) {
                if (matrix[i-1][j-1]) up[i][j] = up[i-1][j] + 1;
                else up[i][j] = 0;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = min(dp[i-1][j-1] + 1, min(l[i][j], up[i][j]));
                ans += dp[i][j];
            }
        }
        return ans;
    }
};