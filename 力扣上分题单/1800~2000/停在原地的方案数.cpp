// https://leetcode.cn/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/



class Solution {
public:
    static constexpr int mod = 1000000007;
    int numWays(int steps, int arrLen) {
        // 最后结果为0的方案

        // three choice 
        // +1 or -1 or 0

        if (arrLen == 1) return 1;

        vector dp(2, vector<long long>(arrLen + 2));
        int cur = 0;

        dp[cur][2] = dp[cur][1] = 1;
        cur ^= 1;

        for (int k = 2; k <= steps; ++k) {
            for (int i = 1; i <= arrLen; ++i) {
                int pre = cur ^ 1;
                if (!dp[pre][i - 1] && !dp[pre][i] && !dp[pre][i + 1]) break;
                dp[cur][i] = (dp[cur ^ 1][i - 1] + dp[cur ^ 1][i] + dp[cur ^ 1][i + 1]) % mod;
            }
            cur ^= 1;
        }

        return dp[cur ^ 1][1];
    }
};