#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll inf = 0x3f3f3f3f3f3f3f3f;
ll dp[50001][51], f[50001][51], sum[50001];

void dfs(int u, int fa, int k, const vector<vector<int>>& g, const vector<int>& nums) {
    sum[u] = nums[u];
    ll mns = 0, mxs = 0;
    for (int v : g[u]) {
        if (v != fa) {
            dfs(v, u, k, g, nums);
            sum[u] += sum[v];
            for (int i = 1; i <= k; ++i) { // dis >= i
                if (dp[u][i] == -inf) dp[u][i] = dp[v][i-1] + nums[u];
                else dp[u][i] += dp[v][i-1];
                if (f[u][i] == inf) f[u][i] = f[v][i-1] + nums[u];
                else f[u][i] += f[v][i-1];
            }
            mns += -f[v][k-1];
            mxs += -dp[v][k-1];
        }
    }
    // 考虑自己取反
    dp[u][0] = max(dp[u][0], mns - nums[u]);
    f[u][0] = min(f[u][0], mxs - nums[u]);
    // 不考虑任何一个取反
    dp[u][k] = max(dp[u][k], sum[u]);
    f[u][k] = min(f[u][k], sum[u]);
    for (int i = k-1; i >= 0; --i) {
        dp[u][i] = max(dp[u][i+1], dp[u][i]);
        f[u][i] = min(f[u][i+1], f[u][i]);
    }
}

class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = -inf;
                f[i][j] = inf;
            }
            sum[i] = 0;
        }
        dfs(0, -1, k, g, nums);
        ll ans = -inf;
        for (int i = 0; i <= k; ++i) {
            ans = max(ans, dp[0][i]);
        }
        return ans;
    }
};