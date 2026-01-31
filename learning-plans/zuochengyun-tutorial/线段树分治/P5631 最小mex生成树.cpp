#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 1e6 + 7;
const int maxm = 2e6 + 7;
const int maxv = 1e5 + 7;

int n, m, ans, flag;
int fa[maxn], siz[maxn], stk[maxn][2], stkSize = 0;
int head[maxv<<2], cnt = 0;
struct Node { int u, v, nxt; } edges[maxm*20];
struct Edge { int u, v, w; } e[maxm];

void addEdge(int h, int u, int v) {
    edges[cnt].u = u;
    edges[cnt].v = v;
    edges[cnt].nxt = head[h];
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
    if (flag) return;
    int mergeCount = 0;
    for (int i = head[rt]; ~i; i = edges[i].nxt) {
        int u = edges[i].u, v = edges[i].v;
        if (merge(u, v)) mergeCount++; 
    }
    if (l == r) {
        if (stkSize == n-1) {
            ans = l;
            flag = 1;
        }
    }
    else {
        dfs(lson);
        dfs(rson);
    }
    rollback(mergeCount);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    sort(e + 1, e + m + 1, [](Edge a, Edge b){ return a.w < b.w; });
    int cur = 0, p = 1;
    while (p <= m && e[p].w == cur) {
        int j = p+1;
        while (j <= m && e[j].w == cur) ++j;
        p = j;
        cur++;
    }
    ans = cur;
    p = 1;
    cur = 0;
    while (p <= m && e[p].w == cur) {
        int j = p+1;
        while (j <= m && e[j].w == cur) ++j;
        // [0, cur), [cur+1, ans)
        for (int i = p; i < j; ++i) {
            if (cur > 0) {
                update(1, 0, ans-1, 0, cur-1, e[i].u, e[i].v);
            }
            if (cur+1 < ans) {
                update(1, 0, ans-1, cur+1, ans-1, e[i].u, e[i].v);
            }
        }
        cur++;
        p = j;
    }
    for (int i = p; i <= m; ++i) {
        update(1, 0, ans-1, 0, ans-1, e[i].u, e[i].v);
    }
    dfs(1, 0, ans-1);
    cout << ans << '\n';
}