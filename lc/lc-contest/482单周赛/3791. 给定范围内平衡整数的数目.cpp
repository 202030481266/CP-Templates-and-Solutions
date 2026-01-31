#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


ll dp[16][300];

class Solution {
public:
    long long countBalanced(long long low, long long high) {
        string lo = to_string(low - 1);
        string hi = to_string(high);
        string s;
        auto dfs = [&](auto&& self, int p, int sum, bool is_limit, bool is_num) -> ll {
            if (p == s.size()) return is_num && sum == 150 ? 1 : 0;
            if (!is_limit && is_num && dp[p][sum] != -1) return dp[p][sum];
            ll res = 0;
            int up = is_limit ? s[p] - '0' : 9;
            if (!is_num) res += self(self, p + 1, sum, false, false);
            for (int i = is_num ? 0 : 1; i <= up; ++i) {
                res += self(self, p + 1, sum + (p & 1 ? -i : i), is_limit && i == up, true);
            }
            if (!is_limit && is_num) dp[p][sum] = res;
            return res;
        };
        s = lo;
        memset(dp, -1, sizeof(dp));
        ll ansL = dfs(dfs, 0, 150, true, false);
        s = hi;
        memset(dp, -1, sizeof(dp));
        ll ansR = dfs(dfs, 0, 150, true, false);
        return ansR - ansL;
    }
};