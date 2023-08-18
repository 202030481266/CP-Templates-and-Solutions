class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        int n = num1.size(), m = num2.size(), dp[m + 1][500];
        memset(dp, -1, sizeof(dp));
        string tmp;
        function<int(int, int, bool, bool)> dfs = [&](int pos, int S, bool is_limit, bool is_num) -> int {
            if (pos == tmp.size()) return S >= min_sum && S <= max_sum;
            if (!is_limit && is_num && dp[pos][S] != -1) return dp[pos][S];
            int res = 0, up = (is_limit ? tmp[pos] - '0' : 9);
            if (!is_num) { 
                res = (res + dfs(pos + 1, S, false, false) % mod) % mod;
                for (int i = 1; i <= up; ++i) 
                    res = (res + dfs(pos + 1, S + i, is_limit && (i == up), true) % mod) % mod;
            } else {
                for (int i = 0; i <= up; ++i)
                    res = (res + dfs(pos + 1, S + i, is_limit && (i == up), true) % mod) % mod;
            }
            if (!is_limit && is_num) dp[pos][S] = res;
            return res;
        };
        tmp = num2;
        int res1 = dfs(0, 0, true, false);
        memset(dp, -1, sizeof(dp));
        tmp = num1;
        int res2 = dfs(0, 0, true, false);
        int ans = 0;
        // cout << res1 << ' ' << res2 << endl;
        for (int i = 0; i < n; ++i) ans += (num1[i] - '0');
        if (ans <= max_sum && ans >= min_sum) return (res1 - res2 + 1 + mod) % mod;
        return (res1 - res2 + mod) % mod;
    }
};