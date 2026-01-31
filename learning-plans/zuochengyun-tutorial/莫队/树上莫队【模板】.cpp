#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MAXM = 200005;

int n, m, arr[MAXN], st[MAXN], ed[MAXN], stk[MAXN], tot, disc[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], ecnt;
int belong[MAXN], bl[MAXN], br[MAXN];
int f[MAXN][20], dep[MAXN];
int ans[MAXN];

struct Query {
    int l, r, id, q_lca;

    Query(): l(0), r(0), id(0), q_lca(0) {}
    Query(int _l, int _r, int _id, int _lca): l(_l), r(_r), id(_id), q_lca(_lca) {}

    bool operator<(const Query& q) const {
        if (belong[l] != belong[q.l]) return belong[l] < belong[q.l];
        return r < q.r;
    }
} qs[MAXN];

void addEdge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; i < 20; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
    stk[++tot] = u;
    st[u] = tot;
    for (int i = head[u]; i; i = nxt[i]) {
        if (to[i] != fa) {
            dfs(to[i], u);
        }
    }
    stk[++tot] = u;
    ed[u] = tot;
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int cnt[MAXN], vis[MAXN], cur;

void add(int idx) {
    if (vis[idx] & 1) {
        --cnt[arr[idx]]; // 1 -> 2
        if (cnt[arr[idx]] == 0) --cur;
    }
    else {
        ++cnt[arr[idx]]; // 0 -> 1
        if (cnt[arr[idx]] == 1) ++cur;
    }
    ++vis[idx];
}

void del(int idx) {
    if (vis[idx] & 1) {
        --cnt[arr[idx]]; // 1 -> 0
        if (cnt[arr[idx]] == 0) --cur;
    }
    else {
        ++cnt[arr[idx]]; // 2 -> 1
        if (cnt[arr[idx]] == 1) ++cur;
    }
    --vis[idx];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        disc[i] = arr[i];
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        if (st[v] < st[u]) swap(u, v);
        int uv_lca = lca(u, v);
        if (uv_lca == u) {
            qs[i] = Query(st[u], st[v], i, 0);
        }
        else {
            qs[i] = Query(ed[u], st[v], i, uv_lca);
        }
    }
    sort(disc + 1, disc + 1 + n);
    int len = static_cast<int>(unique(disc + 1, disc + 1 + n) - disc - 1);
    for (int i = 1; i <= n; ++i) arr[i] = static_cast<int>(lower_bound(disc + 1, disc + 1 + len, arr[i]) - disc);
    int blen = static_cast<int>(sqrt(tot)), bnum = (tot + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(tot, i * blen);
        for (int j = bl[i]; j <= br[i]; ++j) belong[j] = i;
    }
    sort(qs + 1, qs + 1 + m);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int ql = qs[i].l, qr = qs[i].r, qid = qs[i].id;
        while (l < ql) del(stk[l++]);
        while (l > ql) add(stk[--l]);
        while (r < qr) add(stk[++r]);
        while (r > qr) del(stk[r--]);
        if (qs[i].q_lca) {
            add(qs[i].q_lca);
            ans[qid] = cur;
            del(qs[i].q_lca);
        }
        else ans[qid] = cur;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}
