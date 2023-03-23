// https://leetcode.cn/problems/stone-game-iii/



class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector dp(n + 2, vector<int>(2, INT_MIN));
        vector<int> s(n + 1);

        for (int i = 1; i <= n; ++i)
            s[i] = s[i - 1] + stoneValue[i - 1];

        dp[n + 1][1] = dp[n + 1][0] = 0;
        for (int i = n; i >= 1; --i) {
            for (int j = i; j <= min(i + 2, n); ++j) {
                dp[i][0] = max(dp[i][0], s[j] - s[i - 1] - dp[j + 1][1]);
                dp[i][1] = max(dp[i][1], s[j] - s[i - 1] - dp[j + 1][0]);
            }
        }
        if (dp[1][0] == 0) return "Tie";
        else if (dp[1][0] > 0) return "Alice";
        return "Bob";
    }
};