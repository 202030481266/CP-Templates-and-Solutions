#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


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
        vector<int> sum(n + 1, 0);
        vector<int> pre(n + 1, 0);
        vector<int> color(mx + 1, 0);
        int m = 0, left = 0;
        int result = 0, len = 1;
        auto dfs = [&](auto&& dfs_ref, int u, int fa, int val) -> void {
            ++m;
            sum[m] = sum[m-1] + val;
            pre[m] = color[nums[u]];
            color[nums[u]] = m;
            int tmp = left;
            if (left < pre[m]) left = pre[m];
            if (sum[m] - sum[left+1] > result || sum[m] - sum[left+1] == result && m - left < len) {
                result = sum[m] - sum[left+1];
                len = m - left;
            }
            for (auto [v, w] : g[u]) {
                if (v != fa) {
                    dfs_ref(dfs_ref, v, u, w);
                }
            }
            color[nums[u]] = pre[m];
            left = tmp;
            --m;
        };
        dfs(dfs, 0, -1, 0);
        return {result, len};
    }
};