#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int n, m, a[MAXN];
int ql[MAXN], qr[MAXN];
int mn[MAXN << 2], lazy[MAXN << 2];
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], weight[MAXN << 1], tot = 0;

void addEdge(int u, int v, int w) {
    to[++tot] = v;
    nxt[tot] = head[u];
    weight[tot] = w;
    head[u] = tot;
}

void pushup(int rt) {
    mn[rt] = min(mn[ls], mn[rs]);
}

void pushdown(int rt) {
    if (lazy[rt]) {
        mn[ls] += lazy[rt];
        mn[rs] += lazy[rt];
        lazy[ls] += lazy[rt];
        lazy[rs] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    if (l == r) {
        mn[rt] = a[l];
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        mn[rt] += val;
        lazy[rt] += val;
        return;
    }
    pushdown(rt);
    if (R <= mid) update(lson, L, R, val);
    else if (L > mid) update(rson, L, R, val);
    else {
        update(lson, L, mid, val);
        update(rson, mid + 1, R, val);
    }
    pushup(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return mn[rt];
    pushdown(rt);
    if (R <= mid) return query(lson, L, R);
    if (L > mid) return query(rson, L, R);
    return min(query(lson, L, mid), query(rson, mid + 1, R));
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> ql[i] >> qr[i];
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        update(1, 1, n, ql[i], qr[i], -1);
    }
    for (int i = 1; i <= m; ++i) {
        addEdge(ql[i], i, 1);
        addEdge(qr[i] + 1, i, -1);
    }
    int ans = 0, idx = 0;
    for (int i = 1; i <= n; ++i) {
        for (int x = head[i]; x; x = nxt[x]) {
            int v = to[x], w = weight[x];
            update(1, 1, n, ql[v], qr[v], w);
        }
        int res = 0;
        if (i > 1) res = max(res, a[i] - query(1, 1, n, 1, i - 1));
        if (i < n) res = max(res, a[i] - query(1, 1, n, i + 1, n));
        if (ans < res) {
            ans = res;
            idx = i;
        }
    }
    cout << ans << '\n';
    vector<int> b;
    if (ans) {
        for (int i = 1; i <= m; ++i) {
            if (qr[i] < idx || ql[i] > idx) {
                b.push_back(i);
            }
        }
    }
    cout << b.size() << '\n';
    for (int x : b) cout << x << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
}

