#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();
        vector dp(n+1, vector<int>(k+1, -inf));
        vector<int> sum(n+1, 0);
        vector<int> mx(k+1, -inf);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + nums[i-1];
        }
        // dp[i][k] = dp[i-1][k]
        // dp[i][k] = max(dp[j][k-1] + sum[i] - sum[j])
        // dp[i][k] = max(dp[j][k-1] - sum[j]) + sum[i]
        // (j, i], i - j >= m, j <= i-m, [0, i-m]
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        for (int i = m; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                mx[j] = max(mx[j], dp[i-m][j] - sum[i-m]);
            }
            for (int j = 1; j <= k; ++j) {
                dp[i][j] = max(dp[i-1][j], sum[i] + mx[j-1]);
            }
        }
        return dp[n][k];
    }
};
