// https://leetcode.cn/problems/profitable-schemes/



class Solution {
public:
    static constexpr int mod = 1000000007;
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        // we should caculate the profit should not exceed minProfit
        int m = group.size();
        vector dp(n + 1, vector<int>(minProfit));
        vector<int> f(n + 1, 1);

        for_each(dp.begin(), dp.end(), [&](vector<int>& a){
            fill(a.begin(), a.end(), 1);
        });
        for (int i = 0; i < m; ++i)
            for (int j = n; j >= group[i]; --j)
                f[j] = (f[j] + f[j - group[i]]) % mod;
        if (minProfit == 0) return f[n];
        for (int i = 0; i < m; ++i) 
            for (int j = n; j >= group[i]; --j)
                for (int k = minProfit - 1; k >= profit[i]; --k)
                    dp[j][k] = (dp[j][k] + dp[j - group[i]][k - profit[i]]) % mod;
        return (f[n] - dp[n][minProfit - 1] + mod) % mod;
    }
};