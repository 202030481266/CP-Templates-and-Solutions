class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        int dp[n][n];
        memset(dp, 0, sizeof(dp));

        vector<int> sum(n + 1);
        for (int i = 0; i < n; ++i) 
            sum[i + 1] = sum[i] + nums[i];
        
        // dp[l][r] = (sum[l+1][r] - dp[l+1][r] + nums[l] >= dp[l+1][r])
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1; // [i, j]
                if (len == 1) dp[i][i] = nums[i];
                else {
                    dp[i][j] = sum[j + 1] - sum[i] - min(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        return 2 * dp[0][n - 1] >= sum[n];
    }
};