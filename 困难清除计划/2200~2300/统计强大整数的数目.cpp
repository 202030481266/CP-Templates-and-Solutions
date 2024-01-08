class Solution {
    using ll = long long;
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string suffix) {
        ll suffix_num = stoll(suffix);
        string left = to_string(start - 1), right = to_string(finish);

        if (finish < suffix_num) return 0;

        int suffix_len = suffix.length();//[n - suffix_len, n - 1]

        int n, flag;
        ll dp[20];
        string cur;
        function<ll(int,bool,bool)> dfs = [&](int p, bool is_limit, bool is_num) -> ll {
            if (p == n - suffix_len) {
                return (!is_limit || flag) ? 1 : 0;
            }
            if (!is_limit && is_num && dp[p] != -1) return dp[p];
            ll&res = dp[p];
            res = 0;
            int up = min(is_limit ? cur[p] - '0' : 9, limit);
            if (!is_num) { // no number
                res += dfs(p + 1, false, false);
                for (int i = 1; i <= up; ++i) {
                    res += dfs(p + 1, is_limit && i == cur[p] - '0', true);
                }
            }
            else {
                for (int i = 0; i <= up; ++i) {
                    res += dfs(p + 1, i == cur[p] - '0' && is_limit, true);
                }
            }
            return res;
        };
        function<ll(string)> cal = [&](string s) -> ll {
            n = s.size();
            cur = s;
            memset(dp, -1, sizeof(dp));
            string suf = s.substr(n - suffix_len, suffix_len);
            flag = (suf >= suffix ? 1 : 0);
            return dfs(0, true, false);
        };

        ll r = cal(right);
        if (start <= suffix_num) return r;
        return r - cal(left);
    }
};