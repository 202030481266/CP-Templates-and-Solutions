#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {
        vector g(n, vector<pii>{});
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
        }
        vi ops;
        auto dfs = [&](auto&& self, int u, int fa) -> void {
            for (auto [v, idx] : g[u]) {
                if (v != fa) {
                    self(self, v, u);
                    if (target[v] != start[v]) {
                        ops.push_back(idx);
                        start[u] = '0' + '1' - start[u];
                    }
                }
            }
        };
        dfs(dfs, 0, -1);
        if (start[0] != target[0]) return {-1};
        ranges::sort(ops);
        return ops;
    }
};
