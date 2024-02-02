// 区间DP
class Solution {
public:
    int minimumMoves(vector<int>& arr) {
        int n = arr.size();
        int dp[110][110];
        memset(dp, 0, sizeof(dp));

        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (len == 1) dp[i][i] = 1;
                else if (len == 2) dp[i][j] = (arr[i] == arr[j] ? 1 : 2);
                else {
                    if (arr[i] == arr[j]) dp[i][j] = dp[i + 1][j - 1];
                    else dp[i][j] = 0x3f3f3f3f;
                    for (int k = i; k < j; ++k) {
                        if (arr[k] == arr[i]) {
                            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                        }
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};