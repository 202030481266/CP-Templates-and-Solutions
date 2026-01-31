class Solution {
public:
    using ll = long long;
    static constexpr int mod = 1e9 + 7;
    int waysToDistribute(int n, int k) {
        // 组合数学, 第二类stirling number
            // 初始化边界条件
        vector<vector<ll>> dp(n + 1, vector<ll>(k + 1));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;  // 将i个物品分成0个非空循环排列的方法数为0
        }
        for (int j = 0; j <= k; j++) {
            dp[0][j] = 0;  // 将0个物品分成j个非空循环排列的方法数为0
        }
        dp[0][0] = 1;  // 将0个物品分成0个非空循环排列的方法数为1
        // 递推计算
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j] = (j * dp[i - 1][j] % mod + dp[i - 1][j - 1]) % mod;
            }
        }
        return dp[n][k];
    }
};