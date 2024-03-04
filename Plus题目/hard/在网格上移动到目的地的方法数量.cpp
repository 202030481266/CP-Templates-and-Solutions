class Solution {
public:
    using ll = long long;
    const int mod = 1e9 + 7;
    int numberOfWays(int n, int m, int k, vector<int>& source, vector<int>& dest) {
        // 将所有的点都分为4部分，source, x==source_x,y==source_y,source_x!=x&&y!=source_y
        // 可以使用数学归纳法证明这个结论：在k步数下，source到达区域里面任一点计数一样

        vector<vector<ll>> dp(2, vector<ll>(4));
        int pre = 0, cur = 1;
        dp[pre][0] = dp[pre][3] = 0;
        dp[pre][1] = dp[pre][2] = 1;

        for (int i = 2; i <= k; ++i) {
            dp[cur][0] = (dp[pre][1] + dp[pre][2] + dp[pre][0] * (n + m - 4) % mod) % mod;
            dp[cur][1] = (dp[pre][1] * (m - 2) % mod + dp[pre][3] + dp[pre][0] * (n - 1) % mod) % mod;
            dp[cur][2] = (dp[pre][2] * (n - 2) % mod + dp[pre][3] + dp[pre][0] * (m - 1) % mod) % mod;
            dp[cur][3] = (dp[pre][1] * (m - 1) % mod + dp[pre][2] * (n - 1) % mod) % mod;
            swap(pre, cur);
        }

        if (dest[0] == source[0] && dest[1] == source[1]) return dp[pre][3];
        else if (dest[0] == source[0]) return dp[pre][1];
        else if (dest[1] == source[1]) return dp[pre][2];
        else return dp[pre][0];
    }
};