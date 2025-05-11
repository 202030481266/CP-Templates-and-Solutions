// https://codeforces.com/problemset/problem/938/G
// 线段树分治 + 异或线性基
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 7;
const int maxm = 8e6 + 7;
// graph
int head[maxn<<2], to[maxm], nxt[maxm], eCount = 0; 
// dsu
int dis[maxn], siz[maxn], fa[maxn], stk[maxn][2], stkSize = 0;
// xor base
int xorBase[32], xorBaseStk[32], xorSize = 0;
// edges
struct Edge {
    int u, v, w, t;
    bool operator<(const Edge& rhs) const {
        if (u != rhs.u) return u < rhs.u;
        else if (v != rhs.v) return v < rhs.v;
        else return t < rhs.t;
    }
} e[maxn<<1];
// operations
int n, m, q, query[maxn][2];

void addEdge(int rt, int eId) {
    to[eCount] = eId;
    nxt[eCount] = head[rt];
    head[rt] = eCount++;
}
void updateXorBase(int num) {
    for (int i = 30; i >= 0; --i) {
        if ((num>>i) & 1) {
            if (xorBase[i]) num ^= xorBase[i];
            else {
                xorBase[i] = num;
                xorBaseStk[xorSize++] = i;
                break;
            }
        }
    }
}
int queryMinXorBase(int num) { // 必须从高位开始
    for (int i = 30; i >= 0; --i) {
        num = min(num, num ^ xorBase[i]);
    }
    return num;
}
void xorRollBack(int times=1) {
    for (int i = 1; i <= times; ++i) {
        xorBase[xorBaseStk[--xorSize]] = 0; // rollback the added xorBase
    }
}
int find(int x) {
    while (x != fa[x]) x = fa[x];
    return x;
}
int getDis(int x) {
    int res = 0;
    while (x != fa[x]) {
        res ^= dis[x];
        x = fa[x];
    }
    return res;
}
bool merge(int x, int y, int w) {
    int fx = find(x), fy = find(y);
    int d = getDis(x) ^ w ^ getDis(y);
    if (siz[fx] < siz[fy]) swap(fx, fy);
    if (fx == fy) {
        // update xor base, the spanning tree with x-y as a new cycle base
        // path(x, y) ^ w
        updateXorBase(d);
        return false;
    }
    // y ^ dis[y] -> fy, fy ^ dis[y] -> y, y ^ w -> x, x ^ dis[x] -> fx
    dis[fy] = d;
    fa[fy] = fx;
    siz[fx] += siz[fy];
    stk[stkSize][0] = fx;
    stk[stkSize++][1] = fy;
    return true;
}
void dsuRollback(int times=1) {
    for (int i = 0; i < times; ++i) {
        int fx = stk[stkSize-1][0], fy = stk[stkSize-1][1];
        dis[fy] = 0;
        fa[fy] = fy;
        siz[fx] -= siz[fy];
        stkSize--;
    }
}

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid+1, r

void add(int rt, int l, int r, int L, int R, int idx) {
    if (L <= l && r <= R) {
        addEdge(rt, idx);
        return;
    }
    if (R <= mid) add(lson, L, R, idx);
    else if (L > mid) add(rson, L, R, idx);
    else {
        add(lson, L, mid, idx);
        add(rson, mid+1, R, idx);
    }
}
void dfs(int rt, int l, int r) {
    int mergeCnt = 0, preXorSize = xorSize;
    for (int i = head[rt]; ~i; i = nxt[i]) {
        int u = e[to[i]].u, v = e[to[i]].v, w = e[to[i]].w;
        bool flag = merge(u, v, w);
        if (flag) mergeCnt++;
    }
    if (l == r) {
        int x = query[l][0], y = query[l][1];
        if (x && y) {
            int d = getDis(x) ^ getDis(y);
            cout << queryMinXorBase(d) << '\n';
        }
    }
    else {
        dfs(lson);
        dfs(rson);
    }
    if (mergeCnt) dsuRollback(mergeCnt);
    if (xorSize > preXorSize) xorRollBack(xorSize - preXorSize);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
        e[i].t = 0;
    }
    cin >> q;
    for (int i = 1, op, x, y, w; i <= q; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> w;
            if (x > y) swap(x, y);
            e[++m].u = x;
            e[m].v = y;
            e[m].w = w;
            e[m].t = i;
        }
        else if (op == 2) {
            cin >> x >> y;
            if (x > y) swap(x, y);
            e[++m].u = x;
            e[m].v = y;
            e[m].t = i;
        }
        else {
            cin >> x >> y;
            query[i][0] = x;
            query[i][1] = y;
        }
    }
    sort(e + 1, e + m + 1); // [1, m]
    int p = 1;
    while (p <= m) {
        int i = p + 1;
        while (i <= m && e[i].u == e[p].u && e[i].v == e[p].v) ++i;
        for (int j = p; j < i; j += 2) {
            if (j + 1 < i) {
                add(1, 0, q, e[j].t, e[j+1].t-1, j);
            }
            else {
                add(1, 0, q, e[j].t, q, j);
            }
        }
        p = i;
    }
    dfs(1, 0, q);
    return 0;
}
