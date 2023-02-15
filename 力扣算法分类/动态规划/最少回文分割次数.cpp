// https://leetcode.cn/problems/palindrome-partitioning-ii/
// 技巧：自己成为一个新的回文串或者和之前的称为一个总体回文串
// 判断回文串是经典的dp问题

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n + 1, 0);
        vector<vector<bool>> g(n + 1, vector<bool>(n + 1, false));

        for (int i = 1; i <= n; i++) g[i][i] = true;
        for (int len = 2; len <= n; len++) {
            for (int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;
                if (len == 2) g[i][j] = (s[i - 1] == s[j - 1]);
                else g[i][j] = (g[i + 1][j - 1] && s[i - 1] == s[j - 1]);
            }
        }
        dp[1] = 1;
        for (int i = 2; i <= s.size(); i++) {
            dp[i] = dp[i - 1] + 1;
            for (int j = 1; j < i; j++) {
                if (g[j][i]) 
                    dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }
        return dp[n] - 1;
    }
};