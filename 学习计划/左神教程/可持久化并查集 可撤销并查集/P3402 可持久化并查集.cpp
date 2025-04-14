// https://www.luogu.com.cn/problem/P3402
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e5 + 7;
const int maxm = 2e5 + 7;
const int N = maxm * 40;
int n, m, root[maxm], tot = 0, ls[N], rs[N], fa[N], siz[N];

int clone(int x) {
    int y = ++tot;
    ls[y] = ls[x];
    rs[y] = rs[x];
    fa[y] = fa[x];
    siz[y] = siz[x];
    return y;
}
int build(int l, int r) {
    int rt = ++tot;
    if (l == r) {
        fa[rt] = l;
        siz[rt] = 1;
        return rt;
    }
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid+1, r);
    return rt;
}
int update(int rt, int l, int r, int p, int val, int type) {
    int c = clone(rt);
    if (l == r) {
        if (type == 1) fa[c] = val;
        else siz[c] = val;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p, val, type);
    else rs[c] = update(rs[c], mid+1, r, p, val, type);
    return c;
}
int query(int rt, int l, int r, int p, int type) {
    if (l == r) {
        return type == 1 ? fa[rt] : siz[rt];
    }
    int mid = (l + r) >> 1;
    if (p <= mid) return query(ls[rt], l, mid, p, type);
    else return query(rs[rt], mid+1, r, p, type);
}
int find(int x, int version) {
    int fx = query(root[version], 1, n, x, 1);
    while (fx != x) {
        x = fx;
        fx = query(root[version], 1, n, x, 1);
    }
    return x;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    root[0] = build(1, n);
    for (int i = 1, op, a, b, x; i <= m; ++i) {
        cin >> op;
        if (op == 2) {
            cin >> x;
            root[i] = root[x];
        }
        else {
            cin >> a >> b;
            root[i] = root[i-1];
            int fa = find(a, i), fb = find(b, i);
            if (op == 1) {
                if (fa == fb) continue;
                int siza = query(root[i], 1, n, fa, 2);
                int sizb = query(root[i], 1, n, fb, 2);
                if (siza < sizb) swap(fb, fa);
                root[i] = update(root[i], 1, n, fb, fa, 1);
                root[i] = update(root[i], 1, n, fa, siza + sizb, 2);
            }
            else {
                cout << (fa == fb ? 1 : 0) << '\n';
            }
        }
    }
}