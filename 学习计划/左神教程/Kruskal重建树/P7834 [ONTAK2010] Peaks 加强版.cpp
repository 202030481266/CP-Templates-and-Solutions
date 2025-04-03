// https://www.luogu.com.cn/problem/P7834

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 1e5 + 7;
const int maxm = 5e5 + 7;
const int N = maxn * 2;
const int M = N * 25;

int n, m, q, cnt = 0, tot = 0;
int dep[N], fa[N], up[N][20];
int dfn[N], ids[N], val[N], arr[maxn], siz[N], st[N];
int root[maxn], ls[M], rs[M], sz[M], T = 0, b[maxn], bn;
vector<int> g[N];
struct Edge { int u, v, w; } edges[maxm];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void dfs (int u, int father) {
    dep[u] = dep[father] + 1;
    up[u][0] = father;
    for (int i = 1; i < 20; ++i) 
        up[u][i] = up[up[u][i - 1]][i - 1];
    if (u <= n) {
        dfn[u] = ++tot;
        ids[tot] = u;
        siz[u] = 1;
        st[u] = tot;
    }
    for (int v : g[u]) {
        dfs(v, u);
        siz[u] += siz[v];
        if (st[u] == 0) st[u] = st[v];
    }
}
int getBottleneck(int x, int limit) {
    for (int i = 19; i >= 0; --i) {
        if (up[x][i] > 0 && val[up[x][i]] <= limit) {
            x = up[x][i];
        }
    }
    return x;
}
int kth(int x) {
    return lower_bound(b + 1, b + 1 + bn, x) - b;
}
void pushup(int rt) {
    sz[rt] = sz[ls[rt]] + sz[rs[rt]];
}
int clone(int x) {
    int y = ++T;
    ls[y] = ls[x];
    rs[y] = rs[x];
    sz[y] = sz[x];
    return y;
}
int build(int l, int r) {
    int rt = ++T;
    if (l == r) {
        return rt;
    }
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    return rt;
}
int update(int rt, int l, int r, int p) {
    int c = clone(rt);
    if (l == r) {
        sz[c]++;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p);
    else rs[c] = update(rs[c], mid + 1, r, p);
    pushup(c);
    return c;
}
int query(int i, int j, int l, int r, int k) {
    if (l == r) return l;
    int tmp = sz[ls[j]] - sz[ls[i]]; // (i, j]
    if (tmp >= k) return query(ls[i], ls[j], l, (l + r) >> 1, k);
    return query(rs[i], rs[j], ((l + r) >> 1) + 1, r, k - tmp);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> q;
    cnt = n;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        cin >> arr[i];
        b[i] = arr[i];
    }
    sort(b + 1, b + 1 + n);
    bn = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges + 1, edges + m + 1, [](Edge a, Edge b) {
        return a.w < b.w;
    });
    for (int i = 1; i <= m; ++i) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            fa[fu] = fa[fv] = ++cnt;
            fa[cnt] = cnt;
            val[cnt] = w;
            g[cnt].push_back(fu);
            g[cnt].push_back(fv);
        }
    }
    dfs(cnt, 0);
    root[0] = build(1, bn);
    for (int i = 1; i <= n; ++i) {
        root[i] = update(root[i-1], 1, bn, kth(arr[ids[i]]));
    }
    for (int i = 1, u, x, k, lastans = 0; i <= q; ++i) {
        cin >> u >> x >> k;
        u = (u ^ lastans) % n + 1;
        k = (k ^ lastans) % n + 1;
        x = (x ^ lastans);
        int father = getBottleneck(u, x);
        int l = st[father], r = l + siz[father] - 1;
        if (siz[father] < k) {
            cout << "-1\n";
            lastans = 0;
        } else {
            int ans = query(root[l - 1], root[r], 1, bn, siz[father]-k+1);
            cout << b[ans] << '\n';
            lastans = b[ans];
        }
    }
}