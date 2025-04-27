#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 5001;
const int maxm = 5e5 + 7;

int n, m, last[maxn][maxn];
int fa[maxn], siz[maxn], stk[maxn][2], stkSize = 0;
int head[maxm<<2], cnt = 0;
struct edge { int u, v, op; } e[maxm];
struct Edge { int u, v, nxt;  } edge[maxm*10];

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
        if (e[l].op == 2) {
            if (find(e[l].u) == find(e[l].v)) cout << "Y\n";
            else cout << "N\n";
        }
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
        cin >> e[i].op >> e[i].u >> e[i].v;
        if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
        if (e[i].op == 1) {
            update(1, 1, m, last[e[i].u][e[i].v], i-1, e[i].u, e[i].v);
            last[e[i].u][e[i].v] = i;
        }
        else if (e[i].op == 0) {
            last[e[i].u][e[i].v] = i;
        }
    }
    for (int i = m; i >= 1; --i) {
        if (last[e[i].u][e[i].v] == i && e[i].op == 0) {
            update(1, 1, m, i, m, e[i].u, e[i].v);
        } 
    }
    dfs(1, 1, m);
}