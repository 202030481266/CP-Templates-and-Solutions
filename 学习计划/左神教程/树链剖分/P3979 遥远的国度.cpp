// https://www.luogu.com.cn/problem/P3979
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e5 + 7;
int n, m, root, p, r;
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
int a[maxn], mn[maxn<<2], lazy[maxn<<2];

void pushup(int rt) {
    mn[rt] = min(mn[ls], mn[rs]);
}
void pushdown(int rt) {
    if (lazy[rt]) {
        mn[ls] = mn[rs] = lazy[rt];
        lazy[ls] = lazy[rs] = lazy[rt];
        lazy[rt] = 0;
    }
}
void build(int rt, int l, int r) {
    if (l == r) {
        mn[rt] = a[ids[l]];
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        mn[rt] = val;
        lazy[rt] = val;
        return;
    }
    pushdown(rt);
    if (R <= mid) update(lson, L, R, val);
    else if (L > mid) update(rson, L, R, val);
    else {
        update(lson, L, mid, val);
        update(rson, mid+1, R, val);
    }
    pushup(rt);
}
int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return mn[rt];
    }
    pushdown(rt);
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else return min(query(lson, L, mid), query(rson, mid+1, R));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    cin >> root;
    r = root;
    dfs1(root, 0);
    dfs2(root, root);
    build(1, 1, n);
    for (int i = 1, op, x, y, z; i <= m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> root;
        }
        else if (op == 2) {
            cin >> x >> y >> z;
            while (top[x] != top[y]) {
                if (dep[top[x]] >= dep[top[y]]) {
                    update(1, 1, n, dfn[top[x]], dfn[x], z);
                    x = fa[top[x]];
                }
                else {
                    update(1, 1, n, dfn[top[y]], dfn[y], z);
                    y = fa[top[y]];
                }
            }
            update(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), z);
        }
        else {
            cin >> x;
            if (x == root) {
                cout << mn[1] << '\n';
                continue;
            }
            if (dfn[root] < dfn[x] || dfn[root] >= dfn[x] + siz[x]) {
                cout << query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1) << '\n';
            }
            else {
                int u = root;
                while (top[u] != top[x]) {
                    if (fa[top[u]] == x) {
                        u = top[u];
                        break;
                    }
                    u = fa[top[u]];
                }
                if (top[u] == top[x]) {
                    u = son[x];
                }
                int ans = inf;
                if (dfn[u]-1 > 0) ans = min(ans, query(1, 1, n, 1, dfn[u]-1));
                if (dfn[u]+siz[u] <= n) ans = min(ans, query(1, 1, n, dfn[u]+siz[u], n));
                cout << ans << '\n';
            }
        }
    }
}