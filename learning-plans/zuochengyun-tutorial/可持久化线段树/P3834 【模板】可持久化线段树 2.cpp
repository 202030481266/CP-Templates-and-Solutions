// 单点修改 + 范围查询

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 2e5 + 7;
const int N = maxn * 25;

int root[maxn], ls[N], rs[N], siz[N], tot;
int a[maxn], n, m, b[maxn], bn;

int kth(int x) {
    return lower_bound(b + 1, b + 1 + bn, x) - b;
}

void pushup(int rt) {
    siz[rt] = siz[ls[rt]] + siz[rs[rt]];
}

int build(int l, int r) {
    int rt = ++tot;
    if (l == r) {
        siz[rt] = 0;
        return rt;
    }
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    return rt;
}

int clone(int x) {
    int y = ++tot;
    ls[y] = ls[x];
    rs[y] = rs[x];
    siz[y] = siz[x];
    return y;
}

int update(int rt, int l, int r, int p) {
    int c = clone(rt);
    if (l == r) {
        siz[c] += 1;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p);
    else rs[c] = update(rs[c], mid + 1, r, p);
    pushup(c);
    return c;
}

int query(int i, int j, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int sz = siz[ls[j]] - siz[ls[i]];
    int mid = (l + r) >> 1;
    if (sz >= k) {
        return query(ls[i], ls[j], l, mid, k);
    }
    return query(rs[i], rs[j], mid + 1, r, k - sz);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    bn = unique(b + 1, b + 1 + n) - b - 1;
    root[0] = build(1, bn);
    for (int i = 1; i <= n; ++i) {
        root[i] = update(root[i-1], 1, bn, kth(a[i]));
    }
    for (int i = 1, l, r, k; i <= m; ++i) {
        cin >> l >> r >> k;
        cout << b[query(root[l-1], root[r], 1, bn, k)] << '\n';
    }
    return 0;
}