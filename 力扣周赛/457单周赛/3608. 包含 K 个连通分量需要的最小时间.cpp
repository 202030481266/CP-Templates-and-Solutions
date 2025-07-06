#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;

int fa[maxn];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    fa[fx] = fy;
}

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, int k) {
        if (edges.size() == 0) return 0;
        ranges::sort(edges, [&](const auto& a, const auto& b){
            return a[2] > b[2];
        });
        for (int i = 0; i < n; ++i) fa[i] = i;
        int m = n, p = edges[0][2];
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            p = edges[i][2];
            if (find(u) != find(v)) --m;
            if (m < k) break;
            merge(u, v);
        }
        return m >= k ? 0 : p;
    }
};