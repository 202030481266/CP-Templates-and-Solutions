#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e5 + 7;
int n, m, root, p;
int dep[maxn], fa[maxn], dfn[maxn], ids[maxn], siz[maxn];
int son[maxn], top[maxn], tot;
vector<int> g[maxn];

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    fa[u] = f;
    for (int v : g[u]) {
        if (v != f) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
}
void dfs2(int u, int f) {
    dfn[u] = ++tot;
    ids[tot] = u;
    top[u] = f;
    if (!son[u]) return;
    dfs2(son[u], f); 
    for (int v : g[u]) {
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
}
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
ll a[maxn], sum[maxn<<2], lazy[maxn<<2];

void pushup(int rt) {
    sum[rt] = (sum[ls] + sum[rs]) % p;
}
void pushdown(int rt, int l, int r) {
    if (lazy[rt]) {
        lazy[ls] = (lazy[ls] + lazy[rt]) % p;
        lazy[rs] = (lazy[rs] + lazy[rt]) % p;
        sum[ls] = (sum[ls] + lazy[rt] * (mid - l + 1) % p) % p;
        sum[rs] = (sum[rs] + lazy[rt] * (r - mid) % p) % p;
        lazy[rt] = 0;
    }
}
void build(int rt, int l, int r) {
    if (l == r) {
        sum[rt] = a[ids[l]] % p;
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        sum[rt] = (sum[rt] + val * (r - l + 1) % p) % p;
        lazy[rt] = (lazy[rt] + val) % p;
        return;
    }
    pushdown(rt, l, r);
    if (R <= mid) update(lson, L, R, val);
    else if (L > mid) update(rson, L, R, val);
    else {
        update(lson, L, mid, val);
        update(rson, mid+1, R, val);
    }
    pushup(rt);
}
ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    pushdown(rt, l, r);
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else return (query(lson, L, mid) + query(rson, mid+1, R)) % p;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> root >> p;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(root, 0);
    dfs2(root, root);
    build(1, 1, n);
    for (int i = 1, op, x, y, z; i <= m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            while (top[x] != top[y]) {
                if (dep[top[x]] <= dep[top[y]]) {
                    update(1, 1, n, dfn[top[y]], dfn[y], z);
                    y = fa[top[y]];
                }
                else {
                    update(1, 1, n, dfn[top[x]], dfn[x], z);
                    x = fa[top[x]];
                }
            }
            update(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), z);
        }
        else if (op == 2) {
            cin >> x >> y;
            ll ans = 0;
            while (top[x] != top[y]) {
                if (dep[top[x]] <= dep[top[y]]) {
                    ans = (ans + query(1, 1, n, dfn[top[y]], dfn[y])) % p;
                    y = fa[top[y]];
                }
                else {
                    ans = (ans + query(1, 1, n, dfn[top[x]], dfn[x])) % p;
                    x = fa[top[x]];
                }
            }
            ans = (ans + query(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]))) % p;
            cout << ans << '\n';
        }
        else if (op == 3) {
            cin >> x >> z;
            update(1, 1, n, dfn[x], dfn[x]+siz[x]-1, z);
        }
        else {
            cin >> x;
            cout << query(1, 1, n, dfn[x], dfn[x]+siz[x]-1) << '\n';
        }
    }
}