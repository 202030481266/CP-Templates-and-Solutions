class Solution {
public:
    bool winnerSquareGame(int n) {
        int dp[n + 1][2];
        memset(dp, -1, sizeof(dp));
        function<int(int,int)> dfs = [&](int p, int score) -> int {
            if (dp[score][p] != -1) return dp[score][p];
            int& res = dp[score][p];
            res = 0;
            for (int i = 1; i * i <= score; ++i) {
                if (!dfs(p ^ 1, score - i * i)) {
                    res = 1;
                    break;
                }
            }
            return res;
        };
        return dfs(0, n);
    }
};