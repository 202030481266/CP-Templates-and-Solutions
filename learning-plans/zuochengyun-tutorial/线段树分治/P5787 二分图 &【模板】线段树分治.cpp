#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 1e5 + 5;
const int maxm = 2e5 + 5;

int n, m, k;
int fa[maxn<<1], siz[maxn<<1], stk[maxn<<1][2], stkSize = 0;
int head[maxn<<2], cnt = 0; 
int result[maxn];
struct Edge { int u, v, nxt; } edge[maxm*20];

void addEdge(int h, int u, int v) {
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].nxt = head[h];
    head[h] = cnt++;
}
int find(int x) {
    while (x != fa[x]) x = fa[x];
    return x;
}
bool merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    if (siz[fx] < siz[fy]) swap(fx, fy);
    fa[fy] = fx;
    siz[fx] += siz[fy];
    stk[stkSize][0] = fx;
    stk[stkSize++][1] = fy;
    return true;
}
void rollback(int times=1) {
    for (int i = 1; i <= times; ++i) {
        int fx = stk[stkSize-1][0], fy = stk[stkSize-1][1];
        fa[fy] = fy;
        siz[fx] -= siz[fy];
        stkSize--;
    }
}
void init() {
    for (int i = 1; i <= n*2; ++i) {
        fa[i] = i;
        siz[i] = 1;
    }
    memset(head, -1, sizeof(head));
}

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void update(int rt, int l, int r, int L, int R, int u, int v) {
    if (L <= l && r <= R) {
        addEdge(rt, u, v);
        return;
    }
    if (R <= mid) update(lson, L, R, u, v);
    else if (L > mid) update(rson, L, R, u, v);
    else {
        update(lson, L, mid, u, v);
        update(rson, mid + 1, R, u, v);
    }
}
void dfs(int rt, int l, int r) {
    int mergeCount = 0, ans = 1;
    for (int i = head[rt]; ~i; i = edge[i].nxt) {
        int u = edge[i].u, v = edge[i].v;
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            ans = 0;
            break;
        }
        else {
            if (merge(u, v + n)) mergeCount++;
            if (merge(u + n, v)) mergeCount++;
        }
    }
    if (ans) {
        if (l == r) {
            result[l] = 1;
        }
        else {
            dfs(lson);
            dfs(rson);
        }
    }
    rollback(mergeCount);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    init();
    for (int i = 1, u, v, l, r; i <= m; ++i) {
        cin >> u >> v >> l >> r;
        if (u > v) swap(u, v);
        // [l, r-1], [0, k-1]
        l = max(l, 0);
        r = min(r-1, k-1);
        if (l <= r) update(1, 0, k-1, l, r, u, v);
    }
    dfs(1, 0, k-1);
    for (int i = 0; i < k; ++i) {
        if (result[i]) cout << "Yes\n";
        else cout << "No\n";
    }
}