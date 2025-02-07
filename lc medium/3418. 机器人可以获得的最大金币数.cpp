#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins.size(), m = coins[0].size(), dis[n+1][m+1][3];
        memset(dis, -0x3f, sizeof(dis));
        dis[0][1][2] = dis[1][0][2] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dis[i][j][2] = max(dis[i-1][j][2], dis[i][j-1][2]) + coins[i-1][j-1];
                for (int k = 0; k <= 1; ++k) {
                    int& tmp = dis[i][j][k];
                    tmp = max(tmp, max(dis[i-1][j][k], dis[i][j-1][k]) + coins[i-1][j-1]);
                    tmp = max(tmp, max(dis[i-1][j][k+1], dis[i][j-1][k+1]) + max(0, coins[i-1][j-1]));
                }
            }
        }
        return *max_element(dis[n][m], dis[n][m] + 3);
    }
};