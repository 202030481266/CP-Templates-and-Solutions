#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        vector dp(n, vector<int>(k+1));
        for (int i = 1; i <= k; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[j][i] = dp[j][i-1] + stayScore[i-1][j];
                for (int k = 0; k < n; ++k) {
                    if (k != j && dp[k][i-1] + travelScore[k][j] > dp[j][i])
                        dp[j][i] = dp[k][i-1] + travelScore[k][j];
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) ans = max(ans, dp[i][k]);
        return ans;
    }
};