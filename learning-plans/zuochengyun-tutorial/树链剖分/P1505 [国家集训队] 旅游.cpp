#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lc rt<<1
#define rc rt<<1|1
#define mid (l+r>>1)
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
using namespace std;
const int maxn = 200010;
const int inf = 0x3f3f3f3f;
int n,m,cnt,tot,tim,head[maxn],siz[maxn],fa[maxn],dep[maxn];
int top[maxn],dfn[maxn],id[maxn],laz[maxn<<2],son[maxn];
int maxx[maxn<<2],minn[maxn<<2],sum[maxn<<2];
struct edge {int to, next;} e[maxn<<1];
struct node {
    int u, v, w;
    node() {}
    node(int _u,int _v,int _w): u(_u),v(_v),w(_w) {}
} E[maxn];
void add(int from, int to) {
    e[++cnt].to = to;
    e[cnt].next = head[from];
    head[from] = cnt;
}
void fun(int &x, int &y) {int t = x; x = -y; y = -t;}
void pushup(int rt) {
    sum[rt] = sum[lc] + sum[rc];
    maxx[rt] = max(maxx[lc], maxx[rc]);
    minn[rt] = min(minn[lc], minn[rc]);
}
void pushdown(int rt, int l, int r) {
    if (l == r) return;
    if (laz[rt]) {
        laz[lc] ^= 1; laz[rc] ^= 1;
        sum[lc] = -sum[lc]; sum[rc] = -sum[rc];
        fun(maxx[lc], minn[lc]);
        fun(maxx[rc], minn[rc]);
        laz[rt] = 0;
    }
}
void update1(int rt, int l, int r, int pos, int k) {
    if (l == r && l == pos) {
        minn[rt] = maxx[rt] = sum[rt] = k;
        return;
    }
    pushdown(rt, l, r);
    if (pos <= mid) update1(lson, pos, k);
    else update1(rson, pos, k);
    pushup(rt);
}
void update2(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        laz[rt] ^= 1;
        sum[rt] = -sum[rt];
        fun(maxx[rt], minn[rt]);
        return;
    }
    pushdown(rt, l, r);
    if (L <= mid) update2(lson, L, R);
    if (R > mid) update2(rson, L, R);
    pushup(rt);
}
int query_max(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) 
        return maxx[rt];
    pushdown(rt, l, r);
    int ans = -inf;
    if (L <= mid) ans = max(ans, query_max(lson, L, R));
    if (R > mid) ans = max(ans, query_max(rson, L, R));
    return ans;
}
int query_min(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) 
        return minn[rt];
    pushdown(rt, l, r);
    int ans = inf;
    if (L <= mid) ans = min(ans, query_min(lson, L, R));
    if (R > mid) ans = min(ans, query_min(rson, L, R));
    return ans;
}
int query_sum(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) 
        return sum[rt];
    pushdown(rt, l, r);
    int ans = 0;
    if (L <= mid) ans += query_sum(lson, L, R);
    if (R > mid) ans += query_sum(rson, L, R);
    return ans;
}
void dfs1(int u) {
    siz[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u, int anc) {
    top[u] = anc;
    id[u] = ++tot;
    dfn[tot] = u;
    if (!son[u]) return;
    dfs2(son[u], anc);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
void Negate(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        update2(1, 1, n, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (x == y) return;// 这里和下面是处理边的线段树的重要细节
    if (dep[x] > dep[y]) swap(x, y);
    update2(1, 1, n, id[son[x]], id[y]);
}
int ask_sum(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += query_sum(1, 1, n, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (x == y) return ans;
    if (dep[x] > dep[y]) swap(x, y);
    ans += query_sum(1, 1, n, id[son[x]], id[y]);// 注意是son[x]
    return ans;
}
int ask_max(int x, int y) {
    int ans = -inf;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, query_max(1, 1, n, id[top[x]], id[x]));
        x = fa[top[x]];
    }
    if (x == y) return ans;
    if (dep[x] > dep[y]) swap(x, y);
    ans = max(ans, query_max(1, 1, n, id[son[x]], id[y]));// 注意是son[x]
    return ans;
}
int ask_min(int x, int y) {
    int ans = inf;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = min(ans, query_min(1, 1, n, id[top[x]], id[x]));
        x = fa[top[x]];
    }
    if (x == y) return ans;
    if (dep[x] > dep[y]) swap(x, y);
    ans = min(ans, query_min(1, 1, n, id[son[x]], id[y]));// 注意是son[x]
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        ++x; ++y;// 所有的下标从1开始
        E[++tim] = node(x, y, z);
        add(x, y); add(y, x);
    }
    dep[1] = 1; fa[1] = 0;
    dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= tim; i++) {
        int u = E[i].u, v = E[i].v;
        if (dep[u] < dep[v]) swap(u, v);
        update1(1, 1, n, id[u], E[i].w);
    }
    cin>>m;
    int x, y; char s[10];
    while (m--) {
        scanf("%s%d%d", s, &x, &y);
        if (s[0] == 'C') {
            int u = E[x].u, v = E[x].v;
            if (dep[u] < dep[v]) swap(u, v);
            update1(1, 1, n, id[u], y);
        } else if (s[0] == 'N') {
        	++x; ++y;
            Negate(x, y);
        } else if (s[0] == 'S') {
        	++x; ++y;
            printf("%d\n", ask_sum(x, y));
        } else if (s[1] == 'A') {
        	++x; ++y;
            printf("%d\n", ask_max(x, y));
        } else {
        	++x; ++y;
            printf("%d\n", ask_min(x, y));
        }
    }   
    return 0;
}