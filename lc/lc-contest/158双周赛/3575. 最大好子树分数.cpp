// https://leetcode.cn/problems/maximum-good-subtree-score/description/
using ll = long long;

static constexpr int mod = 1e9 + 7;

class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size();
        vector dp(n, vector<ll>(1<<10));
        vector<int> f(n);
        vector<int> a(n, 1);
        for (int i = 0; i < n; ++i) {
            int x = vals[i];
            while (x) {
                int y = x % 10;
                if ((f[i] >> y) & 1) {
                    a[i] = 0;
                    break;
                }
                f[i] |= 1 << y;
                x /= 10;
            }
        }
        vector<int> g[n];
        for (int i = 1; i < n; ++i) g[par[i]].push_back(i);
        vector<int> fathers;
        auto dfs = [&](auto&& self, int u) -> void {
            if (a[u]) {
                dp[u][f[u]] = vals[u];
                int S = ((1<<10) - 1) ^ f[u];
                for (int fa : fathers) {
                    for (int i = S; i > 0; i = (i - 1) & S) {
                        dp[fa][i | f[u]] = max(dp[fa][i | f[u]], vals[u] + dp[fa][i]);
                    }
                    dp[fa][f[u]] = max(dp[fa][f[u]], (ll)vals[u]);
                }
            }
            fathers.push_back(u);
            for (int v : g[u]) {
                self(self, v);
            }
            fathers.pop_back();
        };
        dfs(dfs, 0);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            auto mx = *max_element(dp[i].begin(), dp[i].end());
            ans = (ans + mx % mod) % mod;
        }
        return ans;
    }
};