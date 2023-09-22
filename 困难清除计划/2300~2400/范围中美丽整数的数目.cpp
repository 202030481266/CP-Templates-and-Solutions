// 数位DP模板题目
class Solution {
    int dp[11][11][11][20], m, mod;
    string s;
public:
    int power(int a, int b) {
        int res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a % mod; 
            a = a * a % mod;
        }
        return res;
    }
    int dfs(int i, int odd, int even, int rem, bool is_limit, bool is_num) {
        if (i == m) return (is_num && rem == 0 && odd == even ? 1 : 0);
        if (!is_limit && is_num && dp[i][odd][even][rem] != -1) return dp[i][odd][even][rem];
        int res = 0, up = (is_limit ? s[i] - '0' : 9);
        if (!is_num) {
            res += dfs(i + 1, odd, even, rem, false, false);
            for (int d = 1; d <= up; ++d) 
                res += dfs(i + 1, (d & 1 ? odd + 1 : odd), (d & 1 ? even : even + 1), (rem + d * power(10, m - 1 - i) % mod) % mod, is_limit && d == up, true);
        }
        else {
            for (int d = 0; d <= up; ++d)
                res += dfs(i + 1, (d & 1 ? odd + 1 : odd), (d & 1 ? even : even + 1), (rem + d * power(10, m - 1 - i) % mod) % mod, is_limit && d == up, true);
        }
        if (!is_limit && is_num) dp[i][odd][even][rem] = res;
        return res;
    }
    int cal(int num) {
        memset(dp, -1, sizeof(dp));
        s = to_string(num);
        m = s.size();
        return dfs(0, 0, 0, 0, true, false);
    }
    int numberOfBeautifulIntegers(int low, int high, int k) {
        mod = k;
        return cal(high) - cal(low - 1);
    }
};