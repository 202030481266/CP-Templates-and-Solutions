#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;

int dp[maxn];

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        vector<tuple<int,int,int>> g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1], st = e[2], ed = e[3];
            g[u].emplace_back(v, st, ed);
        }
        for (int i = 0; i < n; ++i) dp[i] = inf;
        priority_queue<pii, vector<pii>, greater<pii>> q;
        q.emplace(0, 0);
        dp[0] = 0;
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (dp[u] != d) continue;
            if (u == n-1) return d;
            for (auto [v, st, ed] : g[u]) {
                if (d <= ed) {
                    int cost = max(st, d) + 1;
                    if (dp[v] > cost) {
                        dp[v] = cost;
                        q.emplace(cost, v);
                    }
                }
            }
        }
        return -1;
    }
};