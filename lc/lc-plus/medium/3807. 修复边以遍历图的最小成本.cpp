#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges, int k) {
        ranges::sort(edges, [&](const auto& a, const auto& b){ return a[2] < b[2]; });
        vi dis(n);
        auto bfs = [&](int eid) -> int {
            fill(dis.begin(), dis.end(), INF);
            queue<int> q;
            q.emplace(0);
            dis[0] = 0;
            vii g(n);
            for (int i = 0; i <= eid; ++i) {
                int u = edges[i][0], v = edges[i][1];
                g[u].push_back(v);
                g[v].push_back(u);
            }
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                if (u == n - 1) return dis[u];
                for (int v : g[u]) {
                    if (dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                }
            }
            return dis[n - 1];
        };
        int l = -1, r = (int)edges.size();
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (bfs(mid) <= k) r = mid;
            else l = mid;
        }
        return r < edges.size() ? edges[r][2] : -1;
    }
};