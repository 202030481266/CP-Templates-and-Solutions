// https://www.luogu.com.cn/problem/P2617
// 动态区间第K小问题，使用整体二分来做（树套树也可做，但是比较吃空间）

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

static constexpr int maxn = 1e5 + 5;
int n, m, a[maxn];
int fenwick[maxn];
int qid[maxn << 2], ans[maxn << 2];
int lstk[maxn << 2], rstk[maxn << 2], lsiz, rsiz;
int esiz;
struct Event { int type, x, y, val; } events[maxn << 2];

inline int lowbit(int x) {
    return x & -x;
}
void add(int x, int val) {
    for (int i = x; i <= n; i += lowbit(i)) {
        fenwick[i] += val;
    }
}
int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += fenwick[i];
    }
    return res;
}
int sum(int l, int r) {
    return sum(r) - sum(l - 1);
}
void dfs(int ql, int qr, int vl, int vr) {
	if (ql > qr) return;
    if (vl == vr) {
        for (int i = ql; i <= qr; ++i) {
            if (events[qid[i]].type == 1) {
                ans[qid[i]] = vl;
            }
        }
        return;
    }
    int mid = (vl + vr) >> 1;
    lsiz = rsiz = 0;
    for (int i = ql; i <= qr; ++i) { // apply, 计算操作对于查询的贡献
        int id = qid[i];
        if (events[id].type == 0) {
            if (events[id].y <= mid) {
                add(events[id].x, events[id].val);
                lstk[lsiz++] = id;
            }
            else {
                rstk[rsiz++] = id;
            }
        }
        else {
            int res = sum(events[id].x, events[id].y);
            if (res >= events[id].val) lstk[lsiz++] = id;
            else rstk[rsiz++] = id, events[id].val -= res; // 这里记得减去res
        }
    }
    for (int i = ql; i <= qr; ++i) { // rollback
        if (events[qid[i]].type == 0) {
            if (events[qid[i]].y <= mid) {
                add(events[qid[i]].x, -events[qid[i]].val);
            }
        }
    }
    // [ql, qr] -> [ql, ql + lsiz - 1], [ql + lsiz, qr]
    for (int i = ql; i < ql + lsiz; ++i) qid[i] = lstk[i - ql];
    for (int i = ql + lsiz; i <= qr; ++i) qid[i] = rstk[i - (ql + lsiz)];
    int len = lsiz;
    dfs(ql + len, qr, mid + 1, vr);
    dfs(ql, ql + len - 1, vl, mid);
}

int main() {
    // ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
        events[esiz++] = {0, i, a[i], 1}; // type, index, new value, change
    }
    char op;
    for (int i = 1, l, r, k, x, y; i <= m; ++i) {
        cin >> op;
        if (op == 'Q') {
            cin >> l >> r >> k;
            events[esiz++] = {1, l, r, k}; // type, l, r, k
        }
        else {
            cin >> x >> y; // a[x] = y
            mx = max(mx, y);
            events[esiz++] = {0, x, a[x], -1};
            events[esiz++] = {0, x, y, 1};
            a[x] = y;
        }
    }
    for (int i = 0; i < esiz; ++i) qid[i] = i; // init qid
    dfs(0, esiz - 1, 0, mx);
    for (int i = 0; i < esiz; ++i) {
        if (events[i].type == 1) {
            cout << ans[i] << '\n';
        }
    }
}