#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

// 不难，本质问题就是求解一棵树的从一个节点出发的最长路径
// 换根DP
class Solution {
public:
    int dfs(int u, int fa, vector<vector<int>>& g, vector<int>& dep, vector<int>& mx, int d) {
        dep[u] = d;
        mx[u] = d;
        for (int& v : g[u]) {
            if (v != fa) {
                int res = dfs(v, u, g, dep, mx, d+1);
                mx[u] = max(mx[u], res);
            }
        }
        return mx[u];
    }
    void cal(int u, int fa, vector<vector<int>>& g, vector<int>& dep, vector<int>& dp, vector<int>& mx) {
        if (fa != u) dp[u] = max(dp[u], dp[fa]+1);
        // deal with its children
        int second = -1, cnt = 1;
        for (int& v : g[u]) {
            if (v != fa) {
                if (mx[v] == mx[u] && cnt) --cnt;
                else second = max(second, mx[v]);
            }
        }
        for (int& v : g[u]) {
            if (v != fa) {
                if (mx[v] == mx[u]) 
                    dp[v] = max(dp[v], second-dep[u]+1);
                else dp[v] = max(dp[v], mx[u]-dep[u]+1);
                cal(v, u, g, dep, dp, mx);
            }
        }
    }
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size()+1, m = edges2.size()+1;
        vector g1(n, vector<int>{});
        vector g2(m, vector<int>{});
        for (auto& e : edges1) g1[e[0]].push_back(e[1]), g1[e[1]].push_back(e[0]);
        for (auto& e : edges2) g2[e[0]].push_back(e[1]), g2[e[1]].push_back(e[0]);
        int mx_r = 0;
        function<int(vector<vector<int>>&,int)> f = [&](vector<vector<int>>& g,int N) -> int {
            vector<int> dp(N), mx(N), dep(N);
            dfs(0,0,g,dep,mx,0);
            cal(0,0,g,dep,dp,mx);
            int ans = 0x3f3f3f3f;
            for (int i = 0; i < N; ++i) {
                int t = max(dp[i], mx[i]-dep[i]);
                ans = min(ans, t);
                mx_r = max(mx_r, t);
            }
            return ans;
        };
        int res1 = f(g1, n), res2 = f(g2, m);
        return max(res1 + res2 + 1, mx_r);
    }
};