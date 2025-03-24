// https://codeforces.com/problemset/problem/741/D
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 5e5 + 7;

int n, val[maxn], dep[maxn], mxdep[(1 << 22) + 7];
int L[maxn], R[maxn], ids[maxn], dfn;
int siz[maxn], son[maxn], ans[maxn];
vector<pii> g[maxn];

void dfs0(int u, int fa) {
    L[u] = ++dfn;
    ids[dfn] = u;
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    for (auto [v, w] : g[u]) {
        val[v] = val[u] ^ (1 << w);
        dfs0(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
    R[u] = dfn;
}
void dfs1(int u, int keep) {
    for (auto [v, w] : g[u]) {
        if (v != son[u]) {
            dfs1(v, 0);
            ans[u] = max(ans[u], ans[v]);
        }
    }
    if (son[u]) {
        dfs1(son[u], 1);
        ans[u] = max(ans[u], ans[son[u]]);
    }
    if (mxdep[val[u]]) ans[u] = max(ans[u], mxdep[val[u]] - dep[u]);
    for (int i = 0; i < 22; ++i) {
        if (mxdep[val[u] ^ (1 << i)])
            ans[u] = max(ans[u], mxdep[val[u] ^ (1 << i)] - dep[u]);
    }
    mxdep[val[u]] = max(mxdep[val[u]], dep[u]);
    for (auto [v, w] : g[u]) {
        if (v != son[u]) {
            for (int i = L[v]; i <= R[v]; ++i) {
                int x = ids[i];
                if (mxdep[val[x]]) ans[u] = max(ans[u], dep[x] + mxdep[val[x]] - 2 * dep[u]);
                for (int i = 0; i < 22; ++i) {
                    if (mxdep[val[x] ^ (1 << i)])
                        ans[u] = max(ans[u], dep[x] + mxdep[val[x] ^ (1 << i)] - 2 * dep[u]);
                }
            }
            for (int i = L[v]; i <= R[v]; ++i) {
                int x = ids[i];
                mxdep[val[x]] = max(mxdep[val[x]], dep[x]);
            }
        }
    }
    if (!keep) {
        for (int i = L[u]; i <= R[u]; ++i) {
            int x = ids[i];
            mxdep[val[x]] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 2, fa; i <= n; ++i) {
        char c;
        cin >> fa >> c;
        g[fa].push_back({i, c - 'a'});
    }
    dfs0(1, 0);
    dfs1(1, 1);
    for (int i = 1; i <= n; ++i) {
        if (i < n) cout << ans[i] << ' ';
        else cout << ans[i] << '\n';
    }
}