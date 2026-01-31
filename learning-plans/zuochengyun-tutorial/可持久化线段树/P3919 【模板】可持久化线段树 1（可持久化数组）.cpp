// 单点查询 + 单点修改

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1e6 + 7;
const int N = maxn * 23;

int root[maxn], ls[N], rs[N], val[N];
int tot = 0, a[maxn], n, m;

// 动态开点
int build(int l, int r) {
    int rt = ++tot;
    if (l == r) {
        val[rt] = a[l];
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
    val[y] = val[x];
    return y;
}

int update(int rt, int l, int r, int p, int v) {
    int c = clone(rt);
    if (l == r) {
        val[c] = v;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p, v);
    else rs[c] = update(rs[c], mid + 1, r, p, v);
    return c;
}

int query(int rt, int l, int r, int p) {
    if (l == r) return val[rt];
    int mid = (l + r) >> 1;
    if (p <= mid) return query(ls[rt], l, mid, p);
    else return query(rs[rt], mid + 1, r, p);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    root[0] = build(1, n);
    int op, version, value, pos;
    for (int i = 1; i <= m; ++i) {
        cin >> version >> op;
        if (op == 1) {
            cin >> pos >> value;
            root[i] = update(root[version], 1, n, pos, value);
        }
        else {
            cin >> pos;
            cout << query(root[version], 1, n, pos) << '\n';
            root[i] = root[version];
        }
    }
    return 0;
}