// https://leetcode.cn/problems/dice-roll-simulation/description/
// 经典的连续出现次数方案数问题，状态设计为 dp[i][j][k] 表示第i为填写为j并且已经填写k次的合法方案数
// 可以使用滚动数组优化


class Solution {
public:
    static constexpr int mod = 1000000007;
    int dieSimulator(int n, vector<int>& rollMax) {
        // 正向反而会简单一点
        vector dp(2, vector(6, vector<long long>(16, 0)));

        int cur = 0;
        for (int i = 0; i < 6; ++i) dp[cur][i][1] = 1;
        cur ^= 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < 6; ++j) {
                for (int t = 1; t <= rollMax[j]; ++t) {
                    for (int p = 0; p < 6; ++p) {
                        if (p != j) {
                            dp[cur][p][1] = (dp[cur][p][1] + dp[cur ^ 1][j][t]) % mod; 
                        } 
                        else {
                            // 1 is calculated
                            if (t + 1 <= rollMax[j])
                                dp[cur][p][t + 1] = (dp[cur][p][t + 1] + dp[cur ^ 1][p][t]) % mod;
                        }
                    }
                }
            }
            cur ^= 1;
            // must be initalized as 0
            for (int i = 0; i < 6; ++i) fill(dp[cur][i].begin(), dp[cur][i].end(), 0);
        }
        long long ans = 0;
        for (int i = 0; i < 6; ++i)
            for (int k = 1; k <= rollMax[i]; ++k)
                ans = (ans + dp[cur ^ 1][i][k]) % mod;
        return ans;

    }
};