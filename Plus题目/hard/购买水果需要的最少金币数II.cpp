class Solution {
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size(), dp[n + 1], q[n + 10];
        memset(dp, 0x3f, sizeof(dp));

        dp[0] = 0;
        int st = 0, ed = 0;

        auto f = [&](int i) -> int {
            return dp[i - 1] + prices[i - 1];
        };
        for (int i = 1; i <= n; ++i) {
            int j = (i & 1 ? i / 2 + 1 : i / 2);
            while (st < ed && f(q[ed - 1]) > f(i)) --ed;
            q[ed++] = i;
            while (st < ed && q[st] < j) ++st;
            dp[i] = f(q[st]);
        }
        return dp[n];
    }
};