#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 在线解法

const int maxn = 2e5 + 7;
const int N = maxn * 23;

int n, m, tot, root[maxn], a[maxn];
int ls[N], rs[N], leftmost[N];  // 将 left 重命名为 leftmost

void pushup(int rt) {
    leftmost[rt] = min(leftmost[ls[rt]], leftmost[rs[rt]]);
}

int build(int l, int r) {
    int rt = ++tot;
    leftmost[rt] = 0;
    if (l == r) return rt;
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    return rt;
}

int update(int rt, int l, int r, int p, int val) {
    int c = ++tot;
    ls[c] = ls[rt], rs[c] = rs[rt], leftmost[c] = leftmost[rt];  // 修复这里的赋值
    if (l == r) {
        leftmost[c] = val;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[rt], l, mid, p, val);
    else rs[c] = update(rs[rt], mid + 1, r, p, val);
    pushup(c);
    return c;
}

int query(int rt, int l, int r, int p) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (leftmost[ls[rt]] < p) return query(ls[rt], l, mid, p);
    else return query(rs[rt], mid + 1, r, p);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    root[0] = build(0, n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] >= 0 && a[i] <= n) {
            root[i] = update(root[i-1], 0, n, a[i], i);
        }
        else {
            root[i] = root[i-1];
        }
    }
    for (int i = 0, l, r; i < m; ++i) {
        cin >> l >> r;
        cout << query(root[r], 0, n, l) << '\n';
    }
    return 0;
}