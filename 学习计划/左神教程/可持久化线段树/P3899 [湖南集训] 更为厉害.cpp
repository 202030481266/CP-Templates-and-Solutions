// 树上问题转换为区间问（dfn序）
// 值域线段树

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 3e5 + 5;
const int N = 23 * maxn;

int n, m, tot, cnt = 0;
int siz[maxn], dep[maxn], dfn[maxn], ids[maxn];
int root[maxn], ls[N], rs[N];
ll sum[N];
vector<int> g[maxn];

int build(int l, int r) {
    int rt = ++tot;
    if (l == r) return rt;
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    return rt;
}

int update(int rt, int l, int r, int p, ll val) {
    int c = ++tot;
    ls[c] = ls[rt], rs[c] = rs[rt], sum[c] = sum[rt];
    if (l == r) {
        sum[c] += val;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p, val);
    else rs[c] = update(rs[c], mid + 1, r, p, val);
    sum[c] = sum[ls[c]] + sum[rs[c]];
    return c;
}

ll query(int x, int y, int l, int r, int L, int R) {
    if (L <= l && r <= R) return sum[y] - sum[x];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(ls[x], ls[y], l, mid, L, R);
    else if (L > mid) return query(rs[x], rs[y], mid + 1, r, L, R);
    else return query(ls[x], ls[y], l, mid, L, mid) + query(rs[x], rs[y], mid + 1, r, mid + 1, R);
}

void dfs(int u, int fa) {
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    dfn[++cnt] = u;
    ids[u] = cnt;
    for (int v : g[u]) {
        if (v != fa) {
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); 
    cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    root[0] = build(1, n);
    for (int i = 1; i <= n; ++i) {
        root[i] = update(root[i-1], 1, n, dep[dfn[i]], siz[dfn[i]]-1);
    }
    ll ans;
    for (int i = 1, p, k; i <= m; ++i) {
        cin >> p >> k;
        // min(dep[p]-1, k) * (siz[p]-1)
        ans = 1ll * (siz[p] - 1) * min(dep[p] - 1, k);
        // [ids[p], ids[p] + siz[p] - 1]
        // [dep[p] + 1, dep[p] + k]
        int l = min(n, dep[p] + 1), r = min(n, dep[p] + k);
        ll res = query(root[ids[p]-1], root[ids[p]+siz[p]-1], 1, n, l, r);
        cout << ans + res << '\n';
    }
}