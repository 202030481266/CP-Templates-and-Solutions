class Solution {
    int dp[2][1010];
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size(), cur = 0;
        memset(dp, 0x3f, sizeof(dp));
        dp[cur ^ 1][500] = 0;
        for (int i = 1; i <= n; ++i) {
            memset(dp[cur], 0x3f, sizeof(dp[cur]));
            for (int j = 0; j <= 1000; ++j) {
                if (j >= time[i - 1] && dp[cur ^ 1][j - time[i - 1]] != 0x3f3f3f3f) 
                    dp[cur][j] = min(dp[cur][j], dp[cur ^ 1][j - time[i - 1]] + cost[i - 1]);
                if (dp[cur ^ 1][j + 1] != 0x3f3f3f3f)
                    dp[cur][j] = min(dp[cur][j], dp[cur ^ 1][j + 1]);
            }
            cur ^= 1;
        }
        int ans = 0x3f3f3f3f;
        for (int i = 500; i <= 1000; ++i)
            ans = min(ans, dp[cur ^ 1][i]);
        return ans;
    }
};