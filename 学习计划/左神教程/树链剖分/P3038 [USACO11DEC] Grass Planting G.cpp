#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 2e5 + 7;
int n, m, root, p;
int dep[maxn], fa[maxn], dfn[maxn], ids[maxn], siz[maxn];
int son[maxn], top[maxn], tot;
vector<int> g[maxn];

// 线段树相关
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r

ll a[maxn], sum[maxn<<2], lazy[maxn<<2];

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
void pushdown(int rt, int l, int r) {
    if (lazy[rt]) {
        lazy[ls] += lazy[rt];
        lazy[rs] += lazy[rt];
        sum[ls] += lazy[rt] * (mid - l + 1);
        sum[rs] += lazy[rt] * (r - mid);
        lazy[rt] = 0;
    }
}
void pushup(int rt) {
    sum[rt] = sum[ls] + sum[rs];
}
// 区间加一
void update(int rt, int l, int r, int L, int R) {
	if (R < L) return;
    if (L <= l && r <= R) {
        sum[rt] += (r - l + 1);
        lazy[rt]++;
        return;
    }
    pushdown(rt, l, r);
    if (R <= mid) update(lson, L, R);
    else if (L > mid) update(rson, L, R);
    else {
        update(lson, L, mid);
        update(rson, mid+1, R);
    }
    pushup(rt);
}
int query(int rt, int l, int r, int L, int R) {
	if (L > R) return 0;
    if (L <= l && r <= R) {
        return sum[rt];
    }
    pushdown(rt, l, r);
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else return query(lson, L, mid) + query(rson, mid+1, R);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    char op;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> op >> u >> v;
        if (op == 'P') {
            while (top[u] != top[v]) {
                if (dep[top[u]] >= dep[top[v]]) {
                    update(1, 1, n, dfn[top[u]], dfn[u]);
                    u = fa[top[u]];
                }
                else {
                    update(1, 1, n, dfn[top[v]], dfn[v]);
                    v = fa[top[v]];
                }
            }
            // 不更新其中的LCA
            update(1, 1, n, min(dfn[u], dfn[v]) + 1, max(dfn[u], dfn[v]));
        }
        else {
            ll ans = 0;
            while (top[u] != top[v]) {
                if (dep[top[u]] >= dep[top[v]]) {
                    ans += query(1, 1, n, dfn[top[u]], dfn[u]);
                    u = fa[top[u]];
                }
                else {
                    ans += query(1, 1, n, dfn[top[v]], dfn[v]);
                    v = fa[top[v]];
                }
            }
            ans += query(1, 1, n, min(dfn[u], dfn[v]) + 1, max(dfn[u], dfn[v]));
            cout << ans << '\n';
        }
    }
}