#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr ll V = 1e15;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int m = edges.size();
        int n = online.size();
        int l = inf, r = -inf;
        for (auto& e : edges) {
            l = min(l, e[2]);
            r = max(r, e[2]);
        }
        --l;
        ++r;
        vector<ll> dis(n);
        vector<int> cnt(n);
        vector<pii> g[n];
        bool find = false;
        auto check = [&](int val) -> bool {
            for (int i = 0; i < n; ++i) {
                dis[i] = V;
                cnt[i] = 0;
                g[i].clear();
            }
            for (auto& e : edges) {
                if (e[2] >= val && online[e[1]] && online[e[0]]) {
                    g[e[0]].emplace_back(e[1], e[2]);
                    ++cnt[e[1]];
                }
            }
            queue<int> q;
            for (int i = 0; i < n; ++i) {
                if (cnt[i] == 0 && online[i]) q.push(i);
            }
            dis[0] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto [v, w] : g[u]) {
                    --cnt[v];
                    dis[v] = min(dis[v], dis[u] + w);
                    if (cnt[v] == 0) {
                        q.push(v);
                    }
                }
            }
            if (dis[n-1] <= k) find = true;
            return dis[n-1] <= k;
        };
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }
        return find ? l : -1;
    }
};