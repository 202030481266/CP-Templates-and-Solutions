#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

const int N = 1e5 + 9;
vii g(N);
int col[N], sz[N], big[N];
ll res = 0, cnt[22], tot[22], ans[N];

void dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
void add(int u, int p, int x) {
    // f(x)=x*(N-x);
    // f(x+1)=f(x)+N-2x-1
    // f(x-1)=f(x)-N+2x-1
    if (x == 1) res += tot[col[u]] - 2 * cnt[col[u]] - 1;
    else res += 2 * cnt[col[u]] - tot[col[u]] - 1;
    cnt[col[u]] += x;
    for (auto v : g[u]) {
        if (v == p || big[v] == 1) continue;
        add(v, u, x);
    }
}
void dsu(int u, int p, bool keep) {
    int bigchild = -1, mx = -1;
    for (auto v : g[u]) {
        if (v == p) continue;
        if (sz[v] > mx) mx = sz[v], bigchild = v;
    }
    for (auto v : g[u]) {
        if (v == p || v == bigchild) continue;
        dsu(v, u, 0);
    }
    if (bigchild != -1) dsu(bigchild, u, 1), big[bigchild] = 1;
    add(u, p, 1);
    ans[u] = res;
    if (bigchild != -1) big[bigchild] = 0;
    if (keep == 0) add(u, p, -1);
}

class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        res = 0;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            sz[i] = big[i] = ans[i] = 0;
        }
        for (int i = 0; i < 22; ++i) cnt[i] = tot[i] = 0;
        for (int i = 0; i < n; ++i) {
            col[i] = group[i];
            ++tot[col[i]];
        }
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dsu(0, -1, false);
        ll final = 0;
        for (int i = 0; i < n; ++i) final += ans[i];
        return final;
    }
};