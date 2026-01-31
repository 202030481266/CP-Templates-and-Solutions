#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// dp 加 颜色位置维护
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = edges.size() + 1, mx = *max_element(nums.begin(), nums.end());
        vector<pii> g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        vector<int> sum(n + 1, 0), ppre(n + 1, 0), pre(n + 1, 0);
        vector<int> color1(mx + 1, 0), color2(mx + 1, 0);
        vector dp(n + 1, vector<int>(2, 0));
        int m = 0, result = 0, len = 1;
        auto dfs = [&](auto&& dfs_ref, int u, int fa, int val) -> void {
            ++m;
            sum[m] = sum[m - 1] + val;
            pre[m] = color1[nums[u]];
            ppre[m] = color2[nums[u]];
            color2[nums[u]] = color1[nums[u]];
            color1[nums[u]] = m;
            if (fa != -1) {
                dp[u][0] = max(dp[fa][0], pre[m]);
                dp[u][1] = min(max(dp[fa][1], pre[m]), max(dp[fa][0], ppre[m]));
            }
            if (sum[m] - sum[dp[u][0] + 1] > result || sum[m] - sum[dp[u][0] + 1] == result && m - dp[u][0] < len) {
                result = sum[m] - sum[dp[u][0] + 1];
                len = m - dp[u][0];
            }   
            if (sum[m] - sum[dp[u][1] + 1] > result || sum[m] - sum[dp[u][1] + 1] == result && m - dp[u][1] < len) {
                result = sum[m] - sum[dp[u][1] + 1];
                len = m - dp[u][1];
            }
            for (auto [v, w] : g[u]) {
                if (v != fa) {
                    dfs_ref(dfs_ref, v, u, w);
                }
            }
            color1[nums[u]] = pre[m];
            color2[nums[u]] = ppre[m];
            --m;
        };
        dfs(dfs, 0, -1, 0);
        return {result, len};
    }
};