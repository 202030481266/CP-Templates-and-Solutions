#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good) {
        vi dp(n), f(n);
        vi g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        auto dfs = [&](auto&& self, int u, int fa) -> void {
            dp[u] = good[u] ? 1 : -1;
            for (int v : g[u]) {
                if (v != fa) {
                    self(self, v, u);
                    if (dp[v] > 0) dp[u] += dp[v];
                }
            }
        };
        auto cal = [&](auto&& self, int u, int fa) -> void {
            for (int v : g[u]) {
                if (v != fa) {
                    if (f[u] < 0) f[v] = dp[v];
                    else {
                        if (dp[v] > 0) f[v] = max(dp[v], f[u]);
                        else f[v] = dp[v] + f[u];
                    }
                    self(self, v, u);
                }
            }
        };
        dfs(dfs, 0, -1);
        f[0] = dp[0];
        cal(cal, 0, -1);
        return f;
    }
};