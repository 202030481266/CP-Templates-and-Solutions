class Solution {
public:
    using ll = long long;
    static constexpr int mod = 1e9 + 7;
    int sumOfPower(vector<int>& nums, int k) {
        int n = nums.size(); 
        ll dp[n + 1][k + 1];
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = dp[i - 1][j]; // 不取
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod; // 取但是不取值
                if (j >= nums[i - 1]) {
                    // cerr << j - nums[i] << endl;
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % mod; // 取但是取值
                }
            }
        }
        return dp[n][k];
    }
};