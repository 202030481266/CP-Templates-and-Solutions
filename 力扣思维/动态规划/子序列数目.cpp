// https://leetcode.cn/problems/distinct-subsequences/
// 求解子序列的构造方案数
// 技巧：公共子序列的变种，枚举匹配的前几个然后转移
// dp[i][j] 表示的是前i个字符和子序列前j个字符匹配的方案数


class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        if (n < m) return 0;

        vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));

        for (int i = 0; i <= n; i++) dp[i][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(m, i); j++) {
                dp[i][j] = dp[i - 1][j];
                if (s[i - 1] == t[j - 1]) dp[i][j] += dp[i - 1][j - 1];
            }
        }
        return dp[n][m];
    }
};
// 滚动数组压缩
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        if (n < m) return 0;

        vector<unsigned long long> dp(m + 1, 0);

        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = min(m, i); j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) dp[j] += dp[j - 1];
            }
        }
        return dp[m];
    }
};