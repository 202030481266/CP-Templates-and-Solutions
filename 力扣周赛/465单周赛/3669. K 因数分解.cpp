#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn  = 100005;

int dp[maxn][6], nxt[maxn][6];

// 非常无语的题目，本质上就是爆搜而已

class Solution {
public:
    vector<int> minDifference(int n, int k) {
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                for (int j = 1; j <= k; ++j) {
                    dp[i][j] = dp[n / i][j] = -1;
                    nxt[i][j] = nxt[n / i][j] = -1;
                }
            }
        }
        vector<int> ans;
        vector<int> use;
        int diff = inf;
        auto dfs = [&](auto&& self, int pre, int cur, int p) -> void {
            if (p == k) {
                if (cur == 1) {
                    int mx = 0, mn = inf;
                    for (int i = 0; i < k; ++i) {
                        if (use[i] > mx) mx = use[i];
                        if (use[i] < mn) mn = use[i];
                    }
                    if (mx - mn < diff) {
                        diff = mx - mn;
                        ans = use;
                    }
                }
                return;
            }
            if (pre > cur) return;
            if (pre * pre > cur) {
                use.push_back(cur);
                self(self, cur, 1, p + 1);
                use.pop_back();
            }
            else {
                for (int i = 1; i * i <= cur; ++i) {
                    if (cur % i == 0) {
                        use.push_back(i);
                        self(self, i, cur / i, p + 1);
                        use.pop_back();
                        if (cur / i >= pre) {
                            use.push_back(cur / i);
                            self(self, cur / i, i, p + 1);
                            use.pop_back();
                        }
                    }
                }
            }
        };
        dfs(dfs, 1, n, 0);
        return ans;
    }
};