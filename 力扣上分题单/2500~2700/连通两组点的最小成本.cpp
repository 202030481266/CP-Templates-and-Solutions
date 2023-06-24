// 超时搜索，对于两边可以枚举所有的情况，然后进行动态规划转移
class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        // 动态规划 1 <= n <= 12 已经表明了这是一个暴力问题
        int n = cost.size(), m = cost[0].size(), dp[1 << n][1 << m];
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i < (1 << n); ++i) 
            for (int j = 1; j < (1 << m); ++j) {
                // 情况转移有三种情况
                for (int x = 0; x < n; ++x) {
                    if ((i >> x) & 1) {
                        for (int y = 0; y < m; ++y) {
                            if ((j >> y) & 1) {
                                dp[i][j] = min(dp[i][j], dp[i ^ (1 << x)][j ^ (1 << y)] + cost[x][y]);
                                dp[i][j] = min(dp[i][j], dp[i ^ (1 << x)][j] + cost[x][y]);
                                dp[i][j] = min(dp[i][j], dp[i][j ^ (1 << y)] + cost[x][y]);
                            }
                        }
                    }
                }
            }
        return dp[(1 << n) - 1][(1 << m) - 1];
    }
};


// 枚举左右两边的选取情况的时候，真的和顺序有关吗？我们发现枚举子集的情况非常冗余，实际上逐步枚举（背包）是完全一样的
// 证明： 假设右边选取情况一致， 左边 1111和可以由一些子集构成，但是可以发现对于一个元素无论先选后选，最后的最优解是一样的，所以不如从头枚举！
class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        // 动态规划 1 <= n <= 12 已经表明了这是一个暴力问题
        int n = cost.size(), m = cost[0].size(), dp[n + 1][1 << m];
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) 
            for (int j = 0; j < (1 << m); ++j) 
                for (int k = 0; k < m; ++k)
                    if ((j >> k) & 1) {
                        dp[i][j] = min(dp[i][j ^ (1 << k)] + cost[i - 1][k], dp[i][j]);
                        dp[i][j] = min(dp[i - 1][j] + cost[i - 1][k], dp[i][j]);
                        dp[i][j] = min(dp[i - 1][j ^ (1 << k)] + cost[i - 1][k], dp[i][j]);
                    }
        return dp[n][(1 << m) - 1];
    }
};





