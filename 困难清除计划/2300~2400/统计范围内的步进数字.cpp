class Solution {
    static constexpr int mod = 1e9 + 7;
    int dp[110][10];
    string s;
    int m;
public:
    int dfs(int i, int pre, bool is_limit, bool is_num) {
        if (i == m) return 1;
        if (!is_limit && is_num && dp[i][pre] != -1) return dp[i][pre];
        int res = 0, up = (is_limit ? s[i] - '0' : 9);
        if (!is_num) {
            res = (res + dfs(i + 1, 0, false, false)) % mod;
            for (int d = 1; d <= up; ++d)
                res = (res + dfs(i + 1, d, is_limit && d == up, true)) % mod;
        }
        else {
            for (int d = 0; d <= up; ++d)
                if (d == pre - 1 || d == pre + 1)
                    res = (res + dfs(i + 1, d, is_limit && d == up, true)) % mod;
        }
        if (!is_limit && is_num) dp[i][pre] = res;
        return res;
    }
    int cal(string x) {
        memset(dp, -1, sizeof(dp));
        s = x;
        m = s.size();
        return dfs(0, 0, true, false);
    }
    int countSteppingNumbers(string low, string high) {
        int ans = (cal(high) - cal(low) + mod) % mod;
        int flag = 1;
        for (int i = 0; i < low.size() - 1; ++i) {
            if (low[i + 1] != low[i] + 1 && low[i + 1] != low[i] - 1) {
                flag = 0;
                break;
            }
        }
        if (flag) return (ans + 1) % mod;
        else return ans;
    }
};