class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size(), m = n / 3; //  做出 m 次选择
        // 环形限定次数打家劫舍问题
        int dp[500][200][2], ans = 0;
        memset(dp, -1, sizeof(dp));
        // 偷取第一个房屋，那么最后一个房屋不能偷取，不用考虑
        dp[1][1][1] = slices[0];
        for (int i = 2; i <= n - 1; ++i) {
            for (int j = 0; j <= min(m, i); ++j) {
                if (j > 0 && dp[i - 1][j - 1][0] != -1)
                    dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - 1][0] + slices[i - 1]);
                if (dp[i - 1][j][0] != -1)
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
                if (dp[i - 1][j][1] != -1)
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][1]);
            }
        }
        ans = max(ans, max(dp[n - 1][m][1], dp[n - 1][m][0]));
        // 偷取最后一个房屋，那么第一个房屋不可能偷取
        memset(dp, -1, sizeof(dp));
        dp[n][1][1] = slices[n - 1];
        for (int i = n - 1; i >= 2; --i) {
            for (int j = 0; j <= min(m, n - i + 1); ++j) {
                if (j > 0 && dp[i + 1][j - 1][0] != -1)
                    dp[i][j][1] = max(dp[i][j][1], dp[i + 1][j - 1][0] + slices[i - 1]);
                if (dp[i + 1][j][0] != -1)
                    dp[i][j][0] = max(dp[i][j][0], dp[i + 1][j][0]);
                if (dp[i + 1][j][1] != -1)
                    dp[i][j][0] = max(dp[i][j][0], dp[i + 1][j][1]);
            }
        }
        ans = max(ans, max(dp[2][m][1], dp[2][m][0]));
        // 两边都不拿
        memset(dp, -1, sizeof(dp));
        dp[1][0][0] = 0;
        for (int i = 2; i <= n - 1; ++i) {
            for (int j = 0; j <= min(m, i); ++j) {
                if (j > 0 && dp[i - 1][j - 1][0] != -1)
                    dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - 1][0] + slices[i - 1]);
                if (dp[i - 1][j][0] != -1)
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
                if (dp[i - 1][j][1] != -1)
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][1]);
            }
        }
        ans = max(ans, max(dp[n - 1][m][0], dp[n - 1][m][1]));
        return ans;
    }
};