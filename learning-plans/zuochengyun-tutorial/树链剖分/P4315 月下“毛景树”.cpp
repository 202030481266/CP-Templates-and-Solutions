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
vector<pii> edges;
vector<int> weight;

// 线段树相关
#define ls rt<<1
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
ll a[maxn], mx[maxn<<2], cover[maxn<<2], add[maxn<<2];

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
void pushdown(int rt) {
    // 如果cover和add同时存在标记，说明是cover之后再加上去的    
    // 这个时候需要先更新cover，再更新add
    if (cover[rt] != -1) {
        cover[ls] = cover[rs] = cover[rt];
        mx[ls] = mx[rs] = cover[rt];
        add[ls] = add[rs] = 0;
        cover[rt] = -1;
    }
    if (add[rt]) {
        add[ls] += add[rt];
        add[rs] += add[rt];
        mx[ls] += add[rt];
        mx[rs] += add[rt];
        add[rt] = 0;
    }
}
void pushup(int rt) {
    mx[rt] = max(mx[ls], mx[rs]);
}
void update(int rt, int l, int r, int L, int R, int type, int val) {
    if (L <= l && r <= R) {
        if (type == 1) {
            cover[rt] = val;
            mx[rt] = val;
            add[rt] = 0;
        }
        else {
            add[rt] += val;
            mx[rt] += val;
        }
        return;
    }
    pushdown(rt);
    if (R <= mid) update(lson, L, R, type, val);
    else if (L > mid) update(rson, L, R, type, val);
    else {
        update(lson, L, mid, type, val);
        update(rson, mid+1, R, type, val);
    }
    pushup(rt);
}
ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return mx[rt];
    }
    pushdown(rt);
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else return max(query(lson, L, mid), query(rson, mid+1, R));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    memset(cover, -1, sizeof(cover)); // 不可能会变为负数个
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        edges.push_back({u, v});
        weight.push_back(w);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 0; i < edges.size(); ++i) {
    	int u = edges[i].first, v = edges[i].second, w = weight[i];
        if (fa[u] == v) update(1, 1, n, dfn[u], dfn[u], 1, w);
        else update(1, 1, n, dfn[v], dfn[v], 1, w);
    }
    string op;
    for (int i = 1, u, v, k, w; ; ++i) {
        cin >> op;
        if (op == "Stop") break;
        if (op == "Change") {
            cin >> k >> w;
            int u = edges[k-1].first, v = edges[k-1].second;
            if (fa[u] == v) update(1, 1, n, dfn[u], dfn[u], 1, w); // cover
            else update(1, 1, n, dfn[v], dfn[v], 1, w);
        }
        else if (op == "Cover" || op == "Add") {
            int type = (op == "Cover" ? 1 : 2);
            cin >> u >> v >> w;
            while (top[u] != top[v]) {
                if (dep[top[u]] >= dep[top[v]]) {
                    update(1, 1, n, dfn[top[u]], dfn[u], type, w);
                    u = fa[top[u]];
                }
                else {
                    update(1, 1, n, dfn[top[v]], dfn[v], type, w);
                    v = fa[top[v]];
                }
            }
            int L = min(dfn[u], dfn[v]) + 1, R = max(dfn[u], dfn[v]);
            if (L <= R) update(1, 1, n, L, R, type, w);
        }
        else {
            cin >> u >> v;
            ll ans = 0;
            while (top[u] != top[v]) {
                if (dep[top[u]] >= dep[top[v]]) {
                    ans = max(ans, query(1, 1, n, dfn[top[u]], dfn[u]));
                    u = fa[top[u]];
                }
                else {
                    ans = max(ans, query(1, 1, n, dfn[top[v]], dfn[v]));
                    v = fa[top[v]];
                }
            }
            int L = min(dfn[u], dfn[v]) + 1, R = max(dfn[u], dfn[v]);
            if (L <= R) ans = max(ans, query(1, 1, n, L, R));
            cout << ans << '\n';
        }
    }
}