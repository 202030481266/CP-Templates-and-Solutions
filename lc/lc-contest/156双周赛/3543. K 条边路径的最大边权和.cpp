#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

using bs = bitset<600>;

bs dp[301][301];

class Solution {
public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        vector<int> cnt(n);
        vector<pii> g[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j].reset();
            }
        }
        for (int i = 0; i < n; ++i) {
            dp[i][0].set(0); // dp[i][0][0] = true;
        }
        for (auto& e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            cnt[e[1]]++;
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, w] : g[u]) {
                if (w < t) {
                    for (int i = 1; i <= k; ++i) {
                        dp[v][i] = dp[v][i] | (dp[u][i-1] << w);
                    }
                }
                --cnt[v];
                if (cnt[v] == 0) q.push(v);
            }
        }
        bs res;
        for (int i = 0; i < n; ++i) {
            res |= dp[i][k];
        }
        for (int i = t - 1; i >= 0; --i) {
            if (res.test(i)) return i;
        }
        return -1;
    }
};