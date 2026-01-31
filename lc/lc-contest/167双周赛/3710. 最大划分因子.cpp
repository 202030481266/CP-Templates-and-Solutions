#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

using vii = vector<vector<int>>;
using vi = vector<int>;

class Solution {
public:
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 2) return 0;
        vii g(n);
        vi color(n, -1);
        auto dfs = [&](auto&& self, int u) -> bool {
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    if (!self(self, v)) {
                        return false;
                    }
                }
                else if (color[v] == color[u]) {
                    return false;
                }
            }
            return true;
        };
        auto cal = [&](int val) -> bool {
            for (int i = 0; i < n; ++i) g[i].clear();
            for (int i = 0; i < n; ++i) {
                color[i] = -1;
                for (int j = i + 1; j < n; ++j) {
                    if (abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]) < val) {
                        g[i].push_back(j);
                        g[j].push_back(i);
                    } 
                }
            }
            for (int i = 0; i < n; ++i) {
                if (color[i] == -1) {
                    color[i] = 0;
                    if (!dfs(dfs, i)) return false;
                }
            }
            return true;
        };
        int l = -1, r = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) r = max(r, abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]) + 1);
        }
        ++r;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (cal(mid)) l = mid;
            else r = mid;
        }
        return l;
    }
};