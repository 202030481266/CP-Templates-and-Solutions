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
int a[maxn], sum[maxn<<2], mx[maxn<<2];

void pushup(int rt) {
    sum[rt] = sum[ls] + sum[rs];
    mx[rt] = max(mx[ls], mx[rs]);
}
void build(int rt, int l, int r) {
    if (l == r) {
        sum[rt] = mx[rt] = a[ids[l]];
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int rt, int l, int r, int p, int val) {
    if (l == r) {
        sum[rt] = mx[rt] = val;
        return;
    }
    if (p <= mid) update(lson, p, val);
    else update(rson, p, val);
    pushup(rt);
}
int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else return (query(lson, L, mid) + query(rson, mid+1, R));
}
int getmax(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return mx[rt];
    }
    if (R <= mid) return getmax(lson, L, R);
    else if (L > mid) return getmax(rson, L, R);
    else return max(getmax(lson, L, mid), getmax(rson, mid+1, R));
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    root = 1;
    dfs1(root, 0);
    dfs2(root, root);
    build(1, 1, n);
    cin >> m;
    string op;
    int ans = 0;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> op;
        if (op == "QMAX") {
            cin >> x >> y;
            ans = -inf;
            while (top[x] != top[y]) {
                if (dep[top[x]] <= dep[top[y]]) {
                    ans = max(ans, getmax(1, 1, n, dfn[top[y]], dfn[y]));
                    y = fa[top[y]];
                }
                else {
                    ans = max(ans, getmax(1, 1, n, dfn[top[x]], dfn[x]));
                    x = fa[top[x]];
                }
            }
            ans = max(ans, getmax(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y])));
            cout << ans << '\n';
        }
        else if (op == "QSUM") {
            cin >> x >> y;
            ans = 0;
            while (top[x] != top[y]) {
                if (dep[top[x]] <= dep[top[y]]) {
                    ans = (ans + query(1, 1, n, dfn[top[y]], dfn[y]));
                    y = fa[top[y]];
                }
                else {
                    ans = (ans + query(1, 1, n, dfn[top[x]], dfn[x]));
                    x = fa[top[x]];
                }
            }
            ans = (ans + query(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y])));
            cout << ans << '\n';
        }
        else {
            cin >> x >> y;
            update(1, 1, n, dfn[x], y);
        }
    }
}