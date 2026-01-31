// https://www.luogu.com.cn/problem/P3834/
// 静态区间第k小的问题

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 7;
int n, m, fenwick[maxn], arr[maxn], ids[maxn]; 
int lStk[maxn], rStk[maxn], ans[maxn], qid[maxn];
int dfsPtr = 1, lSiz = 0, rSiz = 0, qSiz = 0;
struct Query { int l, r, k; } queries[maxn];

inline int lowbit(int x) {
    return x & -x;
}
void add(int pos, int val) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        fenwick[i] += val;
    }
}
int sum(int pos) {
    int res = 0;
    for (int i = pos; i; i -= lowbit(i)) {
        res += fenwick[i];
    }
    return res;
}
void dfs(int ql, int qr, int vl, int vr) {
    if (vl == vr) {
        for (int i = ql; i <= qr; ++i) {
            ans[qid[i]] = arr[ids[vl]];
        }
        return;
    }
    int mid = (vl + vr) / 2;
    lSiz = rSiz = 0;
    while (dfsPtr <= mid) add(ids[dfsPtr++], 1);
    while (dfsPtr > mid + 1) add(ids[--dfsPtr], -1);
    for (int i = ql; i <= qr; ++i) {
        int l = queries[qid[i]].l, r = queries[qid[i]].r;
        bool ok = (sum(r) - sum(l-1) >= queries[qid[i]].k);
        if (ok) lStk[lSiz++] = qid[i];
        else rStk[rSiz++] = qid[i];
    }
    qSiz = ql;
    for (int i = 0; i < lSiz; ++i) qid[qSiz++] = lStk[i];
    for (int i = 0; i < rSiz; ++i) qid[qSiz++] = rStk[i];
    int tmp = lSiz;
    dfs(ql, ql + tmp - 1, vl, mid);
    dfs(ql + tmp, qr, mid+1, vr);
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        ids[i] = i;
    }
    sort(ids + 1, ids + n + 1, [&](int i, int j){
        return arr[i] < arr[j];
    });
    for (int i = 1; i <= m; ++i) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
    }
    for (int i = 1; i <= m; ++i) qid[i] = i;
    dfs(1, m, 1, n);
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}