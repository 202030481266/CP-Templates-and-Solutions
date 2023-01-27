class Solution {
public:
    int maxPalindromes(string s, int k) {
        // dp o(n ^ 2)
        int n = s.size();
        vector<vector<bool>> is_palind(n + 1, vector<bool>(n + 1));
        vector<vector<int>> dp(n + 1, vector<int>(2));

        for (int len = 1; len <= n; len++) {
            for (int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;
                if (len <= 2) {
                    is_palind[i][j] = (s[i - 1] == s[j - 1]);
                } else {
                    is_palind[i][j] = (s[i - 1] == s[j - 1] && is_palind[i + 1][j - 1]);
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
            int temp = -1;
            for (int j = 1; i - j + 1 >= k; j++) {
                if (is_palind[j][i]) 
                    temp = max(dp[j - 1][0], dp[j - 1][1]);
            }
            dp[i][1] = temp + 1;
        }
        return max(dp[n][1], dp[n][0]);
    }
};