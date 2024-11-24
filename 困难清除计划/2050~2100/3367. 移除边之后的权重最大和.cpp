#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size()+1;
        vector dp(n, vector<ll>(2));

        // 反悔贪心

        vector<pii> g[n];
        for (auto&e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v,w});
            g[v].push_back({u,w});
        }

        auto f = [&](int u, int fa, int c) {
            ll& x = dp[u][c]; 
            int cnt = (c == 0 ? k-1 : k);
            priority_queue<pii, vector<pii>, greater<pii>> q;
            for (auto [v, w] : g[u]) {
                if (v == fa) continue;
                if (dp[v][0]+w > dp[v][1]) {
                    if (cnt) {
                        x += dp[v][0]+w;
                        q.emplace(dp[v][0]+w-dp[v][1],v);
                        cnt--;
                    }
                    else {
                        if (!q.empty()) {
                            auto [loss, id] = q.top();
                            if (dp[v][0] + w - loss > dp[v][1]) {
                                q.pop();
                                x += dp[v][0] + w - loss;
                                q.emplace(dp[v][0]+w-dp[v][1],v);
                            }
                            else {
                                x += dp[v][1];
                            }
                        }
                        else {
                            x += dp[v][1];
                        }
                    }
                }
                else {
                    x += dp[v][1];
                }
            }
        };

        auto dfs = [&](int u, int fa, auto&& dfs_ref) -> void {
            for (auto [v, w] : g[u]) {
                if (v == fa) continue;
                dfs_ref(v, u, dfs_ref);
            }
            f(u, fa, 0);
            f(u, fa, 1);
        };
        dfs(0, 0, dfs);
        
        return dp[0][1];
    }
};