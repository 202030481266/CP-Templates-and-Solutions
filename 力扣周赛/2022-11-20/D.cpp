class Solution {
public:
    int beautifulPartitions(string s, int k, int minLength) {
        // beautiful segment
        // start is prime, end is prime
        // 2, 3, 5, 7 and 1, 4, 6, 8, 9
        int n = s.size(), mod = 1000000007;
        vector<bool> is_prime(n + 1, false);
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1));
        vector<vector<long long>> sum(n + 1, vector<long long>(k + 1));
        for (int i = 1; i <= n; i++) {
            int tmp = s[i - 1] - '0';
            if (tmp == 2 || tmp == 3 || tmp == 5 || tmp == 7) is_prime[i] = true;
        }
        // special judge
        if (!is_prime[1]) return 0;
        for (int i = 2; i <= n; i++) {
            if (!is_prime[i] && i >= minLength) {
                dp[i][1] = 1;
                for (int j = 2; j <= k; j++) {
                    int st = (j - 1) * minLength;
                    if (st > i - minLength) break;
                    dp[i][j] = (dp[i][j] + sum[i - minLength][j - 1] - sum[st - 1][j - 1]) % mod;
                    // for (int x = (j - 1) * minLength; x <= i - minLength; x++)
                    //     if (is_prime[x + 1]) res = (res + dp[x][j - 1]) % mod;
                    // dp[i][j] = (dp[i][j] + res) % mod;
                }
            }
            for (int j = 1; j <= k; j++) {
                if (i < n && is_prime[i + 1]) sum[i][j] = (sum[i][j] + dp[i][j]) % mod;
                sum[i][j] = (sum[i][j] + sum[i - 1][j]) % mod;
            }
        }
        return dp[n][k];
    }
};