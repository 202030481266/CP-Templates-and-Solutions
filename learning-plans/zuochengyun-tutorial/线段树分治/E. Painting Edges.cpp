#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 5e5 + 3;
const int maxm = 1e7 + 1;
const int maxk = 51;

int n, m, K, Q; 
struct Edge { int to, nxt; }; // 160MB左右
struct Node { int u, v; } node[maxn];
struct Query { int e, c; } query[maxn];
Edge edge[maxm];
int head[maxn<<2], cnt = 0;
int fa[maxk][maxn<<1], siz[maxk][maxn<<1], stk[maxn<<1][3], stkSize = 0;
int lastEdgePos[maxn], lastColor[maxn], result[maxn];

int find(int c, int x) {
    while (x != fa[c][x]) x = fa[c][x];
    return x;
}
bool merge(int c, int x, int y) {
    int fx = find(c, x), fy = find(c, y);
    if (fx == fy) return false;
    if (siz[c][fx] < siz[c][fy]) swap(fx, fy);
    fa[c][fy] = fx;
    siz[c][fx] += siz[c][fy];
    stk[stkSize][0] = c;
    stk[stkSize][1] = fx;
    stk[stkSize++][2] = fy;
    return true;
}
void rollback(int times=1) {
    for (int i = 1; i <= times; ++i) {
        int c = stk[stkSize-1][0], fx = stk[stkSize-1][1], fy = stk[stkSize-1][2];
        fa[c][fy] = fy;
        siz[c][fx] -= siz[c][fy];
        stkSize--;
    }
}
void init() {
    for (int i = 1; i <= K; ++i) {
        for (int j = 1; j <= 2 * n; ++j) {
            fa[i][j] = j;
            siz[i][j] = 1;
        }
    }
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v) {
    edge[cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt++;
}

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void update(int rt, int l, int r, int L, int R, int op) {
    if (L <= l && r <= R) {
        addEdge(rt, op);
        return;
    }
    if (R <= mid) update(lson, L, R, op);
    else if (L > mid) update(rson, L, R, op);
    else {
        update(lson, L, mid, op);
        update(rson, mid + 1, R, op);
    }
}
void dfs(int rt, int l, int r) {
    int mergeCount = 0, ans = 1;
    for (int i = head[rt]; ~i; i = edge[i].nxt) {
        int op = edge[i].to, e = query[op].e, c = lastColor[e];
        if (c == 0) continue;
        int u = node[e].u, v = node[e].v;
        int fu = find(c, u), fv = find(c, v);
        if (fu != fv) {
            if (merge(c, u, v + n)) ++mergeCount;
            if (merge(c, v, u + n)) ++mergeCount;
        }
        else {
            ans = 0;
            break;
        }
    }
    if (ans) {
        if (l == r) {
            int e = query[l].e, c = query[l].c;
            int u = node[e].u, v = node[e].v;
            int fu = find(c, u), fv = find(c, v);
            if (fu != fv) {
                lastColor[e] = c;
                result[l] = 1;
            }
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
    cin >> n >> m >> K >> Q;
    init();
    for (int i = 1; i <= m; ++i) cin >> node[i].u >> node[i].v;
    for (int i = 1; i <= Q; ++i) cin >> query[i].e >> query[i].c;
    for (int i = Q; i >= 1; --i) {
        if (lastEdgePos[query[i].e]) {
            update(1, 1, Q, i+1, lastEdgePos[query[i].e], i);
        }
        else {
        	if (i+1 <= Q)
        		update(1, 1, Q, i+1, Q, i);
        }
        lastEdgePos[query[i].e] = i;
    }
    dfs(1, 1, Q);
    for (int i = 1; i <= Q; ++i) {
        if (result[i]) cout << "YES\n";
        else cout << "NO\n";
    }
}