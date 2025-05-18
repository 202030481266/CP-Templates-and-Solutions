// https://www.luogu.com.cn/problem/P1527
// 静态二维区域第k小
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 507;
constexpr int N = maxn * maxn;
constexpr int maxq = 6e4 + 7;

int sum[maxn][maxn], n, q, m, xy[N][2];
int arr[N], ids[N], lStk[maxq], rStk[maxq], qid[maxq];
int ans[maxq], dfsPtr = 1, lSiz, rSiz, qSiz;
struct Query { int x1, y1, x2, y2, k; } queries[maxq];

inline int lowbit(int i) { return i & -i; }
void add(int x, int y, int val) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            sum[i][j] += val;
        }
    }
}
int getSum(int x, int y) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        for (int j = y; j; j -= lowbit(j)) {
            res += sum[i][j];
        }
    }
    return res;
}
int getSum(int x1, int y1, int x2, int y2) {
    return getSum(x2, y2) - getSum(x1-1, y2) - getSum(x2, y1-1) + getSum(x1-1, y1-1);
}
void dfs(int ql, int qr, int vl, int vr) {
    if (ql > qr) return;
#ifdef DEBUG
	cout << "debug :" << ql << ' ' << qr << ' ' << vl << ' ' << vr << endl;
    for (int i = ql; i <= qr; ++i) {
    	int id = qid[i];
    	cout << queries[id].x1 << ' ' << queries[id].y1 << ' ' << queries[id].x2 << ' ' << queries[id].y2 << ' ' << queries[id].k << endl;
    }
#endif
    if (vl == vr) {
        for (int i = ql; i <= qr; ++i) {
            ans[qid[i]] = arr[ids[vl]];
        }
        return;
    }
    int mid = (vl + vr) / 2;
    while (dfsPtr <= mid) {
        add(xy[ids[dfsPtr]][0], xy[ids[dfsPtr]][1], 1);
        ++dfsPtr;
    }
    while (dfsPtr > mid + 1) {
        --dfsPtr;
        add(xy[ids[dfsPtr]][0], xy[ids[dfsPtr]][1], -1);
    }
    lSiz = rSiz = 0;
    for (int i = ql; i <= qr; ++i) {
        int x1 = queries[qid[i]].x1, y1 = queries[qid[i]].y1;
        int x2 = queries[qid[i]].x2, y2 = queries[qid[i]].y2;
#ifdef DEBUG
        printf("Check Query Result of (%d, %d, %d, %d), dfsPtr is %d, result is %d\n", x1, y1, x2, y2, dfsPtr, getSum(x1,y1,x2,y2)); 
#endif
        bool ok = getSum(x1, y1, x2, y2) >= queries[qid[i]].k;
        if (ok) lStk[lSiz++] = qid[i];
        else rStk[rSiz++] = qid[i];
    }
    qSiz = ql;
    int tmp = lSiz;
    for (int i = 0; i < lSiz; ++i) qid[qSiz++] = lStk[i];
    for (int i = 0; i < rSiz; ++i) qid[qSiz++] = rStk[i];
    dfs(ql, ql + tmp - 1, vl, mid);
    dfs(ql + tmp, qr, mid+1, vr);
}

int main() {
#ifndef DEBUG
    ios::sync_with_stdio(false); cin.tie(nullptr);
#endif
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> arr[++m];
            ids[m] = m;
            xy[m][0] = i;
            xy[m][1] = j;
        }
    }
    sort(ids + 1, ids + m + 1, [&](int i, int j) {
        return arr[i] < arr[j]; 
    });
#ifdef DEBUG
    for (int i = 1; i <= m; ++i) {
        cout << arr[ids[i]] << ' '<< xy[ids[i]][0] << ' ' << xy[ids[i]][1] << endl;
    }
#endif
    for (int i = 1; i <= q; ++i) {
        qid[i] = i;
        cin >> queries[i].x1 >> queries[i].y1 >> queries[i].x2 >> queries[i].y2 >> queries[i].k;
    }
    dfs(1, q, 1, m);
    for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}