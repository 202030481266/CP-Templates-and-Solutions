#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 50001;

int fa[maxn];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    fa[fy] = fx;
}

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges, int k) {
        sort(edges.begin(), edges.end(), [&](const auto& a, const auto& b) {
            return a[2] < b[2];
        });
        for (int i = 0; i < n; ++i) fa[i] = i;
        if (n == k) return 0;
        for (auto& e : edges) {
            if (find(e[0]) != find(e[1])) {
                --n;
            }
            merge(e[0], e[1]);
            if (n == k) {
                return e[2];
            }
        }
        return 0;
    }
};