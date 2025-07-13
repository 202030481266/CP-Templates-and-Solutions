#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 15;

int vis[maxn][maxn][1 << maxn];

class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int s = 0; s < (1 << n); ++s) {
                    vis[i][j][s] = 0;
                }
            }
        }
        queue<tuple<int,int,int>> q;
        vector g(n, vector<int>());
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
            if (label[u] == label[v]) {
                int s = ((1 << u) | (1 << v));
                if (!vis[u][v][s]) {
                    vis[u][v][s] = vis[v][u][s] = 1;
                    q.emplace(u, v, (1 << u) | (1 << v));
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            vis[i][i][1<<i] = 1;
            q.emplace(i, i, 1 << i);
        }
        int ans = 0;
        while (!q.empty()) {
            auto [u, v, s] = q.front();
            q.pop();
            ans = max(ans, __builtin_popcount(s));
            for (int x : g[u]) {
                if ((s >> x) & 1) continue;
                for (int y : g[v]) {
                    if ((s >> y) & 1) continue;
                    if (y == x || label[y] != label[x]) continue;
                    int ns = (s | (1 << x) | (1 << y));
                    if (!vis[x][y][ns]) {
                        vis[x][y][ns] = vis[y][x][ns] = 1;
                        q.emplace(x, y, s | (1 << x) | (1 << y));
                    }
                }
            }
        }
        return ans;
    }
};