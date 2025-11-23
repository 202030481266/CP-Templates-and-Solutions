#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    ll cal(ll num) {
        string s = to_string(num);
        int n = s.size();
        static ll dp[20][10][3];
        static ll f[20][10][3];
        memset(dp, -1, sizeof(dp));
        auto dfs = [&](auto&& self, int p, int pre, int status, int sum, bool is_limit, int is_num) -> pair<ll, ll> {
            if (p == n) return {sum, 1};
            if (!is_limit && is_num > 1 && dp[p][pre][status] != -1) return {dp[p][pre][status] + f[p][pre][status] * sum, f[p][pre][status]};
            ll res = 0, cnt = 0;
            int up = is_limit ? s[p] - '0' : 9;
            if (!is_num) { 
                auto [x, y] = self(self, p + 1, pre, status, sum, false, 0);
                res += x;
                cnt += y;
            }
            for (int i = is_num ? 0 : 1; i <= up; ++i) {
                int c = 0;
                if (is_num > 1 && status == 1 && i < pre) ++c;
                if (is_num > 1 && status == 2 && i > pre) ++c;
                int ns = (i == pre ? 0 : (i > pre ? 1 : 2));
                auto [x, y] = self(self, p + 1, i, ns, c, is_limit && i == up, is_num + 1);
                res += x;
                cnt += y;
            }
            if (!is_limit && is_num > 1) {
                dp[p][pre][status] = res;
                f[p][pre][status] = cnt;
            }
            return {res + cnt * sum, cnt};
        };
        auto result = dfs(dfs, 0, 0, 0, 0, true, 0);
        return result.first;
    }
    long long totalWaviness(long long num1, long long num2) {
        return cal(num2) - cal(num1 - 1);
    }
};