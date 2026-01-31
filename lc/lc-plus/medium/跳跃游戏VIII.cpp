#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<ll, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;

// 单调栈
class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& costs) {
        int n = nums.size();
        stack<int> s1,s2;
        vector<int> f(n,n), g(n,n);
        vector<ll> dp(n,infll);
        for (int i = 0; i < n; ++i) {
            while (!s1.empty() && nums[s1.top()] > nums[i]) {
                f[s1.top()] = i;
                s1.pop();
            }
            s1.push(i);
            while (!s2.empty() && nums[s2.top()] <= nums[i]) {
                g[s2.top()] = i;
                s2.pop();
            }
            s2.push(i);
        }
        dp[0] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> q; // dijkstra
        q.emplace(0,0);
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (d != dp[u]) continue;
            if (f[u] < n && d + costs[f[u]] < dp[f[u]]) {
                dp[f[u]] = d + costs[f[u]];
                q.emplace(dp[f[u]], f[u]);
            }
            if (g[u] < n && d + costs[g[u]] < dp[g[u]]) {
                dp[g[u]] = d + costs[g[u]];
                q.emplace(dp[g[u]], g[u]);
            }
        }
        return dp[n-1];
    }

};
