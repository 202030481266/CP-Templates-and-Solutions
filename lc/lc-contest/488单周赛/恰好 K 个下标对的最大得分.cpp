#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


ll dp[101][101][101];
class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int x = 0; x <= k; ++x) dp[i][j][x] = -LLINF;
            }
        }
        dp[0][0][0] = 0;
        ll ans = -LLINF;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int x = 0; x <= min(k, min(i, j)); ++x) {
                    if (x > 0) dp[i][j][x] = dp[i - 1][j - 1][x - 1] + 1ll * nums1[i - 1] * nums2[j - 1];
                    if (i > 0) dp[i][j][x] = max(dp[i][j][x], dp[i - 1][j][x]);
                    if (j > 0) dp[i][j][x] = max(dp[i][j][x], dp[i][j - 1][x]);
                }
            }
        }
        return dp[n][m][k];
    }
};
