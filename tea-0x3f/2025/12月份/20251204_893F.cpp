// Problem: F. Subtree Minimum Query
// Contest: Codeforces - Educational Codeforces Round 33 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/893/F
// Memory Limit: 512 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int MAXN = 100005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

#define mid ((l+r)>>1)

static constexpr int MAX_NODE = 10000007;

int n, r, m, a[MAXN], root[MAXN], dep[MAXN];
int ls[MAX_NODE], rs[MAX_NODE], mn[MAX_NODE], use = 0;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot = 0;

void addEdge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        if (to[i] != fa) {
            dfs(to[i], u);
        }
    }
}

inline void pushup(int rt) {
    mn[rt] = min(mn[ls[rt]], mn[rs[rt]]);
}

void modify(int &rt, int l, int r, int pos, int val) {
    if (rt == 0) rt = ++use;
    if (l == r) {
        mn[rt] = min(mn[rt], val);
        return;
    }
    if (pos <= mid) modify(ls[rt], l, mid, pos, val);
    else modify(rs[rt], mid + 1, r, pos, val);
    pushup(rt);
}

int merge(int a, int b, int l, int r) {
    if (a == 0 || b == 0) return a + b;
    int rt = ++use;
    if (l == r) {
        mn[rt] = min(mn[a], mn[b]);
        return rt;
    }
    ls[rt] = merge(ls[a], ls[b], l, mid);
    rs[rt] = merge(rs[a], rs[b], mid + 1, r);
    pushup(rt);
    return rt;
}

int query(int rt, int l, int r, int L, int R) {
	if (rt == 0) return mn[0];
    if (L <= l && r <= R) return mn[rt];
    if (R <= mid) return query(ls[rt], l, mid, L, R);
    if (L > mid) return query(rs[rt], mid + 1, r, L, R);
    return min(query(ls[rt], l, mid, L, mid), query(rs[rt], mid + 1, r, mid + 1, R));
}

void build(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            build(v, u);
            root[u] = merge(root[u], root[v], 1, n);
        }
    }
}

void solve() {
    cin >> n >> r;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(r, 0);
    memset(mn, 0x3f, (n + 1) * 40 * sizeof(int));
    for (int i = 1; i <= n; ++i) {
        modify(root[i], 1, n, dep[i], a[i]);
    }
    build(r, 0);
    int lastAns = 0, x, k;
    cin >> m;
    while (m--) {
        cin >> x >> k;
        x = (x + lastAns) % n + 1;
        k = (k + lastAns) % n;
        lastAns = query(root[x], 1, n, dep[x], min(n, dep[x] + k));
        cout << lastAns << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}