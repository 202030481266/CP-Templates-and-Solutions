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
int fa[maxn], siz[maxn], stk[maxn][2], stkSize = 0;
int head[maxn<<2], cnt = 0;
int last[maxm];
struct Edge { int u, v, nxt; } edge[maxm*30];
struct edge { int u, v; } e[maxm];

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
    for (int i = 1; i <= n; ++i) {
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
    int mergeCount = 0;
    for (int i = head[rt]; ~i; i = edge[i].nxt) {
        int u = edge[i].u, v = edge[i].v;
        if (merge(u, v)) mergeCount++;
    }
    if (l == r) {
        cout << (stkSize == n-1 ? "Connected" : "Disconnected") << '\n';
    }
    else {
        dfs(lson);
        dfs(rson);
    }
    rollback(mergeCount);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v;
        if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
    }
    cin >> k;
    for (int i = 1, tot, x; i <= k; ++i) {
        cin >> tot;
        for (int j = 1; j <= tot; ++j) {
            cin >> x;
            // (last, i)
            if (last[x] + 1 < i) {
                update(1, 1, k, last[x] + 1, i - 1, e[x].u, e[x].v);
            }
            last[x] = i;
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (last[i] + 1 <= k) {
            update(1, 1, k, last[i] + 1, k, e[i].u, e[i].v);
        }
    }
    dfs(1, 1, k);
}