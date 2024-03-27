int dp[510][510];
class Solution {
public:
    int minOperations(string s1, string s2, int x) {
        int n = s1.size();

        vector<int> index;
        for (int i = 0; i < n; ++i)
            if (s1[i] != s2[i]) index.push_back(i);

        int m = index.size(), ans = 0;
        if (m & 1) return -1;
        if (m == 0) return 0;

        auto cost = [&](int i, int j) -> int {
            return min(x, index[j] - index[i]);
        };

        memset(dp, 0x3f, sizeof(dp));
        // 区间dp + 构造
        for (int len = 2; len <= m; len += 2) {
            for (int i = 0; i + len - 1 < m; ++i) {
                int j = i + len - 1;
                if (len == 2) {
                    dp[i][j] = min(dp[i][j], cost(i, j));
                }
                else {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j - 1] + cost(i, j));
                    for (int k = i + 1; k < j - 1; k += 2) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                    }
                }
            }
        }
        return dp[0][m - 1];
    }
};