#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 100005;
static constexpr int maxb = 320;

int n, m, flag, bnum, lastans, arr[maxn];
int bl[maxb], br[maxb], b[maxn];
int dfn[maxn], ids[maxn], son[maxn], f[maxn], dep[maxn], siz[maxn], top[maxn], dcnt = 0;
bitset<30001> bs[maxb], ans;
vector<int> g[maxn];

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    f[u] = fa;
    for (int& v : g[u]) {
        if (v != fa) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
}

void dfs2(int u, int ff) {
    dfn[u] = ++dcnt;
    ids[dcnt] = u;
    top[u] = ff;
    if (!son[u]) return;
    dfs2(son[u], ff);
    for (int& v : g[u]) {
        if (v != son[u] && v != f[u]) {
            dfs2(v, v);
        }
    }
}

void query(int l, int r) {
    if (b[l] == b[r]) {
        for (int i = l; i <= r; ++i) {
            ans[arr[ids[i]]] = 1;
        }
    }
    else {
        for (int i = l; i <= br[b[l]]; ++i) {
            ans[arr[ids[i]]] = 1;
        }
        for (int i = bl[b[r]]; i <= r; ++i) {
            ans[arr[ids[i]]] = 1;
        }
        for (int i = b[l] + 1; i < b[r]; ++i) {
            ans |= bs[i];
        }
    }
}

void update(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        query(dfn[top[x]], dfn[x]);
        x = f[top[x]];
    }
    query(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> flag;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    int blen = sqrt(n * 20);
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(n, i * blen);
        for (int j = bl[i]; j <= br[i]; ++j) {
            b[j] = i;
            bs[i].set(arr[ids[j]]);
        }
    }
    for (int i = 1, c, x, y; i <= m; ++i) {
        cin >> c;
        ans.reset();
        while (c--) {
            cin >> x >> y;
            if (flag) {
                x ^= lastans;
                y ^= lastans;
            }
            update(x, y);
        }
        int ans1 = ans.count(), ans2 = 30001;
        for (int i = 0; i <= 30000; ++i) {
            if (!ans.test(i)) {
                ans2 = i;
                break;
            }
        }
        cout << ans1 << ' ' << ans2 << '\n';
        lastans = ans1 + ans2;
    }
}