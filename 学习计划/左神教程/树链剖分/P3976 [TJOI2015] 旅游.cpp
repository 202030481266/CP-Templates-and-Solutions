// https://www.luogu.com.cn/problem/P3976
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 5e4 + 7;

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

struct node {
    int lx, rx, mx, mn, lazy;
} tree[maxn<<2];
int a[maxn];

void pushup(int rt) {
    tree[rt].lx = max(max(tree[ls].lx, tree[rs].lx), tree[rs].mx - tree[ls].mn);
    tree[rt].rx = max(max(tree[rs].rx, tree[ls].rx), tree[ls].mx - tree[rs].mn);
    tree[rt].mx = max(tree[ls].mx, tree[rs].mx);
    tree[rt].mn = min(tree[ls].mn, tree[rs].mn);
}
void pushdown(int rt, int l, int r) {
    if (tree[rt].lazy) {
        tree[ls].lazy += tree[rt].lazy;
        tree[rs].lazy += tree[rt].lazy;
        tree[ls].mx += tree[rt].lazy;
        tree[ls].mn += tree[rt].lazy;
        tree[rs].mx += tree[rt].lazy;
        tree[rs].mn += tree[rt].lazy;
        tree[rt].lazy = 0;
    }
}
void build(int rt, int l, int r) {
    if (l == r) {
        tree[rt].mx = tree[rt].mn = a[ids[l]];
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        tree[rt].mx += val;
        tree[rt].mn += val;
        tree[rt].lazy += val;
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
node merge(node left, node right) {
    node res;
    res.mx = max(left.mx, right.mx);
    res.mn = min(left.mn, right.mn);
    res.lx = max(max(left.lx, right.lx), right.mx - left.mn);
    res.rx = max(max(right.rx, left.rx), left.mx - right.mn);
    return res;
}
node query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[rt];
    }
    pushdown(rt, l, r);
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else {
        node left = query(lson, L, mid);
        node right = query(rson, mid+1, R);
        return merge(left, right);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; 
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    cin >> m;
    for (int i = 1, x, y, z; i <= m; ++i) {
        cin >> x >> y >> z;
        // x -> y
        node ans1, ans2;
        int u = x, v = y, flag1 = 0, flag2 = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] >= dep[top[y]]) {
                node res = query(1, 1, n, dfn[top[x]], dfn[x]);
                if (flag1) ans1 = merge(res, ans1);
                else ans1 = res, flag1 = 1;
                x = fa[top[x]];
            }
            else {
                node res = query(1, 1, n, dfn[top[y]], dfn[y]);
                if (flag2) ans2 = merge(res, ans2);
                else ans2 = res, flag2 = 1;
                y = fa[top[y]];
            }
        }
        if (dep[x] > dep[y]) {
            node res = query(1, 1, n, dfn[y], dfn[x]);
            if (flag1) ans1 = merge(res, ans1);
            else ans1 = res, flag1 = 1;
        }
        else {
            node res = query(1, 1, n, dfn[x], dfn[y]);
            if (flag2) ans2 = merge(res, ans2);
            else ans2 = res, flag2 = 1;
        }
        if (flag1 && flag2) {
            cout << max(max(ans1.rx, ans2.lx), ans2.mx - ans1.mn) << '\n';
        }
        else if (flag1) {
            cout << ans1.rx << '\n';
        }
        else if (flag2) {
            cout << ans2.lx << '\n';
        }
        else {
            cout << 0 << '\n';
        }
        while (top[u] != top[v]) {
            if (dep[top[u]] >= dep[top[v]]) {
                update(1, 1, n, dfn[top[u]], dfn[u], z);
                u = fa[top[u]];
            }
            else {
                update(1, 1, n, dfn[top[v]], dfn[v], z);
                v = fa[top[v]];
            }
        }
        update(1, 1, n, min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), z);
    }
}