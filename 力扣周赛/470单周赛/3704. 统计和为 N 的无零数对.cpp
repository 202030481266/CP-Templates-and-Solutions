#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

ll dp[20][2];
int g[20][2];

class Solution {
public:
    long long countNoZeroPairs(long long N) {
        string s = to_string(N);
        int n = s.size();
        memset(dp, -1, sizeof(dp));
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 2; ++j) {
                ll num = N / (ll)pow(10, n - 1 - i) - j;
                if (num >= 0) {
                    g[i][j] = 2;
                    if (num) {
                        string tmp = to_string(num);
                        for (char c : tmp) {
                            if (c == '0') {
                                g[i][j] = 0;
                                break;
                            }
                        }
                    }
                    else g[i][j] = 1;
                }
            }
        }
        auto dfs = [&](auto&& self, int p, int one) -> ll {
            if (p < 0) return (one ? 0 : 1);
            if (dp[p][one] != -1) return dp[p][one];
            ll& res = dp[p][one];
            res = p < n - 1 ? g[p][one] : 0;
            if (s[p] - '0' == 0) {
                int limit = (one ? 9 : 10);
                for (int i = 1; i < limit; ++i) res += self(self, p - 1, 1);
            }
            else {
                int limit = (one ? s[p] - '0' - 1 : s[p] - '0');
                for (int i = 1; i < limit; ++i) res += self(self, p - 1, 0);
                for (int i = limit + 1; i < 10; ++i) res += self(self, p - 1, 1);
            }
            return res;
        };
        ll ans = dfs(dfs, n - 1, 0);
        return ans;
    }
};