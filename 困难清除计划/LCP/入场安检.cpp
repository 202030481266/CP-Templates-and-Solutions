class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int securityCheck(vector<int>& capacities, int k) {
        int n = capacities.size();

        // 队列不会影响数字的顺序 
        // 唯一的影响因素在于栈的使用

        for (int& v : capacities) --v;

        int dp[2][k + 1];
        memset(dp, 0, sizeof(dp));

        int pre = 0, cur = 1;
        dp[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            memset(dp[cur], 0, sizeof(dp[cur]));
            for (int j = 0; j <= k; ++j) {
                dp[cur][j] = dp[pre][j];
                if (j >= capacities[i]) dp[cur][j] = (dp[cur][j] + dp[pre][j - capacities[i]]) % mod;
            }
            pre ^= 1;
            cur ^= 1;
        }
        return dp[pre][k];
    }
};