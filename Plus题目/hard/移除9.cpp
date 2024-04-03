// 二分 + 数位DP
class Solution {
public:
    int dp[12][2], mx;
    string s;
    int dfs(int p, int is_limit, int is_num, int have_9) {
        if (p == s.size()) return is_num && have_9 ? 1 : 0; 
        if (!is_limit && is_num && dp[p][have_9] != -1) return dp[p][have_9];
        int res = 0, up = (is_limit ? s[p] - '0' : 9);
        if (!is_num) {
            res += dfs(p + 1, false, false, have_9);
            for (int i = 1; i <= up; ++i) {
                res += dfs(p + 1, is_limit && i == up, true, have_9 | (i == 9));
            }
        }
        else {
            for (int i = 0; i <= up; ++i) {
                res += dfs(p + 1, is_limit && i == up, true, have_9 | (i == 9));
            }
        }
        if (!is_limit && is_num) dp[p][have_9] = res;
        return res;
    }
    int newInteger(int n) {
        // 二分
        auto check = [&](int val) -> bool {
            memset(dp, -1, sizeof(dp));
            s = to_string(val);
            mx = val;
            return val - dfs(0, true, false, 0) >= n;
        };

        int l = -1, r = INT_MAX - 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }
};
