// https://codeforces.com/problemset/problem/891/C
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 5e5 + 7;
int n, m, q, index, fa[maxn], siz[maxn], invalid[maxn], stk[maxn][2], stkSize = 0;
struct edge { int u, v, w; } edges[maxn];
struct query { int eid, qid, ew, eu, ev; } queries[maxn];

int find(int x) {
    while (x != fa[x]) x = fa[x];
    return x;
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (siz[fx] < siz[fy]) swap(fx, fy);
    fa[fy] = fx;
    siz[fx] += siz[fy];
    stk[stkSize][0] = fx;
    stk[stkSize++][1] = fy;
}
void rollback(int times) {
    for (int i = 1; i <= times; ++i) {
        int fx = stk[stkSize-1][0], fy = stk[stkSize-1][1];
        fa[fy] = fy;
        siz[fx] -= siz[fy];
        stkSize--;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1;
    for (int i = 1; i <= m; ++i) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    cin >> q;
    for (int i = 1, qs; i <= q; ++i) {
        cin >> qs;
        for (int j = 0, eid; j < qs; ++j) {
            cin >> eid;
            queries[index].eid = eid;
            queries[index].qid = i;
            queries[index].eu = edges[eid].u;
            queries[index].ev = edges[eid].v;
            queries[index++].ew = edges[eid].w;
        }
    }
    sort(queries, queries + index, [](query a, query b) {
        if (a.ew != b.ew) return a.ew < b.ew;
        return a.qid < b.qid;
    });
    sort(edges + 1, edges + m + 1, [](edge a, edge b) { return a.w < b.w; });
    int last = 1, p = 0;
    while (p < index) {
        int i = p + 1, qid = queries[p].qid, ew = queries[p].ew;
        while (last <= m && edges[last].w < ew) {
            int u = edges[last].u, v = edges[last].v;
            if (find(u) != find(v)) {
                merge(u, v);
            }
            ++last;
        }
        while (i < index && queries[i].qid == qid && queries[i].ew == ew) ++i;
        if (!invalid[qid]) {
            int ops = 0;
            for (int j = p; j < i; ++j) {
                int eu = queries[j].eu, ev = queries[j].ev;
                if (find(eu) != find(ev)) {
                    merge(eu, ev);
                    ++ops;
                }
                else {
                    invalid[qid] = 1;
                    break;
                }
            }
            rollback(ops);
        }
        p = i;
    }
    for (int i = 1; i <= q; ++i) {
        if (!invalid[i]) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}