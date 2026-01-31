class Solution {
public:
    // 爆搜策略
    bool canIWin(int maxChoosableInteger, int desiredTotal) {

        if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) return false;

        int dp[1<<maxChoosableInteger];
        memset(dp, -1, sizeof(dp));

        function<int(int)> dfs = [&](int s) -> int {
            if (dp[s] != -1) return dp[s];
            int& res = dp[s], cur = 0;
            res = 0;
            for (int i = 0; i < maxChoosableInteger; ++i)
                if (!((s >> i) & 1)) cur += i + 1;
            for (int i = 0; i < maxChoosableInteger; ++i) {
                if (i + 1 + cur >= desiredTotal && ((s >> i) & 1)) {
                    res = 1;
                    break;
                }
            }
            if (!res) {
                for (int i = 0; i < maxChoosableInteger; ++i)
                    if ((s >> i) & 1) {
                        if (!dfs(s ^ (1 << i))) {
                            res = 1;
                            break;
                        }
                    }
            }
            return res;
        };
        return dfs((1 << maxChoosableInteger) - 1);
    }
};