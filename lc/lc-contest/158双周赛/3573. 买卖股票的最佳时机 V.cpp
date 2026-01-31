// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-v/description/

using ll = long long;

static constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        // dp[x-1][j-1] + prices[i] - prices[x]
        // dp[x-1][j-1] + prices[x] - prices[i]
        vector dp(n + 1, vector<ll>(k + 1, -inf));
        vector<ll> a(k + 1, -inf), b(k + 1, -inf);
        a[0] = -prices[0]; // dp[0][0] - prices[1]
        b[0] = prices[0];  // dp[0][0] + prices[1]
        dp[0][0] = dp[1][0] = 0;
        for (int i = 2; i <= n; ++i) {
            dp[i][0] = 0;
            for (int j = 1; j <= min(i / 2, k); ++j) {
                dp[i][j] = max(dp[i-1][j], max(a[j-1] + prices[i-1], b[j-1] - prices[i-1]));
            }
            for (int j = 0; j <= min(i / 2, k); ++j) {
                a[j] = max(a[j], dp[i-1][j] - prices[i-1]);
                b[j] = max(b[j], dp[i-1][j] + prices[i-1]);
            }
        }
        return *max_element(dp[n].begin(), dp[n].end());
    }
};