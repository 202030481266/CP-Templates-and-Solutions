// 区间更新 + 区间查询
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1e5 + 7;
const int N = maxn * 70;

int root[maxn], a[maxn], tot, n, m;
int ls[N], rs[N];
ll sum[N], tag[N];

int clone(int x) {
    int y = ++tot;
    ls[y] = ls[x];
    rs[y] = rs[x];
    sum[y] = sum[x];
    tag[y] = tag[x];
    return y;
}

void pushup(int rt) {
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
}

void pushdown(int rt, int l, int r) {
    if (tag[rt]) {
        ls[rt] = clone(ls[rt]);
        rs[rt] = clone(rs[rt]);
        int mid = (l + r) >> 1;
        sum[ls[rt]] += tag[rt] * (mid - l + 1); 
        sum[rs[rt]] += tag[rt] * (r - mid);
        tag[ls[rt]] += tag[rt];
        tag[rs[rt]] += tag[rt];
        tag[rt] = 0;
    }
}

int build(int l, int r) {
    int rt = ++tot;
    if (l == r) {
        sum[rt] = a[l];
        return rt;
    }
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    pushup(rt);
    return rt;
}

int update(int rt, int l, int r, int L, int R, int z) {
    int c = clone(rt);
    if (L <= l && r <= R) {
        sum[c] += (r - l + 1) * z;
        tag[c] += z;
        return c;
    }
    int mid = (l + r) >> 1;
    pushdown(c, l, r);
    if (R <= mid) {
        ls[c] = update(ls[c], l, mid, L, R, z);
    }
    else if (L > mid) {
        rs[c] = update(rs[c], mid + 1, r, L, R, z);
    }
    else {
        ls[c] = update(ls[c], l, mid, L, mid, z);
        rs[c] = update(rs[c], mid + 1, r, mid + 1, R, z);
    }
    pushup(c);
    return c;
}

ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll ans = 0;
    if (R <= mid) ans = query(ls[rt], l, mid, L, R);
    else if (L > mid) ans = query(rs[rt], mid + 1, r, L, R);
    else ans = query(ls[rt], l, mid, L, mid) + query(rs[rt], mid + 1, r, mid + 1, R);
    pushup(rt);
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    root[0] = build(1, n);
    char op;
    for (int i = 1, l, r, t = 0, d; i <= m; ++i) {
        cin >> op;
        if (op == 'C') {
            cin >> l >> r >> d;
            root[t + 1] = update(root[t], 1, n, l, r, d);
            ++t;
        }
        else if (op == 'Q') {
            cin >> l >> r;
            cout << query(root[t], 1, n, l, r) << '\n';
        }
        else if (op == 'H') {
            cin >> l >> r >> d;
            cout << query(root[d], 1, n, l, r) << '\n';
        }
        else {
            cin >> t;
        }
    }
    return 0;
}