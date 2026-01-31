#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    long long maxScore(vector<vector<int>>& edges) {
        // 最大独立集
        int n = edges.size();
        vector<pii> g[n];
        for (int i = 1; i < n; ++i) {
            g[i].emplace_back(edges[i][0], edges[i][1]);
            g[edges[i][0]].emplace_back(i, edges[i][1]);
        }
        // dp[u][1] = max(dp[v][0] + weight[u][v] + sum(max(dp[x][0], dp[x][1]))
        // dp[u][0] = sum(max(dp[x][0], dp[x][1]))
        vector dp(n, vector<ll>(2, 0));
        function<void(int,int)> dfs = [&](int u, int fa) {
            for (auto [v, w] : g[u]) {
                if (v == fa) continue;
                dfs(v, u);
                dp[u][0] += max(dp[v][1], dp[v][0]);
            }
            for (auto [v, w] : g[u]) {
                if (v == fa) continue;
                ll mx = max(dp[v][1], dp[v][0]);
                dp[u][1] = max(dp[u][1], dp[v][0] + w + dp[u][0] - mx);
            }
        };
        dfs(0,-1);
        return max(dp[0][0], dp[0][1]);
    }
};