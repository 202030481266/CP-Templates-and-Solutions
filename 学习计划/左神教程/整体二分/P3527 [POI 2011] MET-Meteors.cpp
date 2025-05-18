//https://www.luogu.com.cn/problem/P3527

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

constexpr int maxn = 3e5 + 7;
int n, m, k;
int req[maxn];
ll sum[maxn<<1];
int head[maxn], to[maxn], nxt[maxn], eCnt = 0;
int lStk[maxn], rStk[maxn], qid[maxn]; 
int lSiz, rSiz, dfsPtr = 1, qSiz;
int ans[maxn];
struct Operation { int l, r, val; } operations[maxn];

void addEdge(int u, int v) {
    to[eCnt] = v;
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}
inline int lowbit(int i) { return i & -i; }
void add(int x, int val) {
    for (int i = x; i <= m * 2; i += lowbit(i)) sum[i] += val;
}
void add(int l, int r, int val) {
    add(l, val);
    add(r+1, -val);
}
int getSum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += sum[i];
    return res;
}
void dfs(int ql, int qr, int vl, int vr) {
	if (ql > qr) return;
    if (vl == vr) {
        if (vl <= k) {
            for (int i = ql; i <= qr; ++i) {
                ans[qid[i]] = vl;
            }
        }
        return;
    }
    int mid = (vl + vr) / 2;
    while (dfsPtr <= mid) {
        add(operations[dfsPtr].l, operations[dfsPtr].r, operations[dfsPtr].val);
        ++dfsPtr;
    }
    while (dfsPtr > mid + 1) {
        --dfsPtr;
        add(operations[dfsPtr].l, operations[dfsPtr].r, -operations[dfsPtr].val);
    }
    lSiz = rSiz = 0;
    for (int i = ql; i <= qr; ++i) {
        ll tot = 0;
        for (int j = head[qid[i]]; ~j; j = nxt[j]) {
            tot += getSum(to[j]) + getSum(to[j] + m);
            if (tot >= req[qid[i]]) break;
        }
        if (tot >= req[qid[i]]) lStk[lSiz++] = qid[i];
        else rStk[rSiz++] = qid[i];
    }
    qSiz = ql;
    for (int i = 0; i < lSiz; ++i) qid[qSiz++] = lStk[i];
    for (int i = 0; i < rSiz; ++i) qid[qSiz++] = rStk[i];
    int tmp = lSiz;
    dfs(ql, ql + tmp - 1, vl, mid);
    dfs(ql + tmp, qr, mid + 1, vr);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 1, j; i <= m; ++i) {
        cin >> j; // j -> i
        addEdge(j, i);
    }
    for (int i = 1; i <= n; ++i) cin >> req[i];
    cin >> k;
    for (int i = 1, l, r; i <= k; ++i) {
        cin >> l >> r >> operations[i].val;
        if (r < l) r += m;
        operations[i].l = l;
        operations[i].r = r;
    }
    for (int i = 1; i <= n; ++i) qid[i] = i;
    dfs(1, n, 1, k + 1);
    for (int i = 1; i <= n; ++i) {
        if (ans[i]) cout << ans[i] << '\n';
        else cout << "NIE" << '\n';
    }
}