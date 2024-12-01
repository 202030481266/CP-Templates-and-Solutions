#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 想了挺久的，应该没有超过 n^2 或者 n*k 其他的思路

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size()+1, m = edges2.size()+1;
        vector g1(n, vector<int>());
        vector g2(m, vector<int>());

        for (auto& e : edges1) {
            int u = e[0], v = e[1];
            g1[u].push_back(v);
            g1[v].push_back(u);
        }
        for (auto& e : edges2) {
            int u = e[0], v = e[1];
            g2[u].push_back(v);
            g2[v].push_back(u);
        }

        vector<int> ans(n);
        if (k == 0) return vector<int>(n,1);
        if (k == 1) {
            for (int i = 0; i < n; ++i) ans[i] = g1[i].size()+2;
            return ans;
        }
        vector c1(n, vector<int>(k+1));
        vector c2(m, vector<int>(k+1));
        auto dfs = [&](int u, int fa, vector<vector<int>>& g, vector<vector<int>>& c, auto&& dfs_ref) -> void {
            c[u][0] = 1;
            for (int& v : g[u]) {
                if (v != fa) {
                    dfs_ref(v, u, g, c, dfs_ref);
                    for (int i = 1; i <= k; ++i) {
                        c[u][i] += c[v][i-1];
                    }
                }
            }
        };
        dfs(0, 0, g1, c1, dfs);
        dfs(0, 0, g2, c2, dfs);
        
        vector dp1(n, vector<int>(k+1));
        vector dp2(m, vector<int>(k+1));
        auto cal = [&](int u, int fa, vector<vector<int>>&g, vector<vector<int>>& dp, vector<vector<int>>& c, auto&& f) -> void {
            for (int v : g[u]) {
                if (v != fa) {
                    dp[v][0] = 1;
                    for (int i = 0; i < k; ++i) {
                        dp[v][i+1] = dp[u][i] - (i > 0 ? c[v][i-1] : 0) + c[v][i+1];
                    }
                    f(v, u, g, dp, c, f);
                }
            }
        };
        for (int i = 0; i <= k; ++i) dp1[0][i] = c1[0][i];
        for (int i = 0; i <= k; ++i) dp2[0][i] = c2[0][i];
        cal(0, 0, g1, dp1, c1, cal);
        cal(0, 0, g2, dp2, c2, cal);
        int mx = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 1; j <= k-1; ++j) {
                dp2[i][j] += dp2[i][j-1];
            }
            if (mx < dp2[i][k-1]) mx = dp2[i][k-1];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp1[i][j] += dp1[i][j-1];
            }
            ans[i] = dp1[i][k] + mx;
        }
        return ans;
    }
};