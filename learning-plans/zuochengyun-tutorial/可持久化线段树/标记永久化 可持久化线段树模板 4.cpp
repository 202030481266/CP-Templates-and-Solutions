// 范围累加和， 区间修改 + 区间查询
// 测试链接：https://acm.hdu.edu.cn/showproblem.php?pid=4348

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1e5 + 7;
const int N = maxn * 25;

int root[maxn], a[maxn], tot, n, m;
int ls[N], rs[N];
ll sum[N], tag[N];

int build(int l, int r) {
    int rt = ++tot;
    if (l == r) {
        sum[rt] = a[l];
        return rt;
    }
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    return rt;
}

int update(int rt, int l, int r, int L, int R, ll z) {
    int c = ++tot, left = max(l, L), right = min(r, R);
    ls[c] = ls[rt];
    rs[c] = rs[rt];
    sum[c] = sum[rt] + (right - left + 1) * z;
    tag[c] = tag[rt];
    if (L <= l && r <= R) {
        tag[c] += z;
        return c;
    }
    int mid = (l + r) >> 1;
    if (R <= mid) ls[c] = update(ls[c], l, mid, L, R, z);
    else if (L > mid) rs[c] = update(rs[c], mid + 1, r, L, R, z);
    else {
        ls[c] = update(ls[c], l, mid, L, mid, z);
        rs[c] = update(rs[c], mid + 1, r, mid + 1, R, z);
    }
    return c;
}

ll query(int rt, int l, int r, int L, int R, ll tag_sum) {
    if (L <= l && r <= R) return sum[rt] + tag_sum * (r - l + 1);
    int mid = (l + r) >> 1;
    if (R <= mid) return query(ls[rt], l, mid, L, R, tag_sum + tag[rt]);
    else if (L > mid) return query(rs[rt], mid + 1, r, L, R, tag_sum + tag[rt]);
    else return query(ls[rt], l, mid, L, mid, tag_sum + tag[rt]) + query(rs[rt], mid + 1, r, mid + 1, R, tag_sum + tag[rt]);
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
            cout << query(root[t], 1, n, l, r, 0) << '\n';
        }
        else if (op == 'H') {
            cin >> l >> r >> d;
            cout << query(root[d], 1, n, l, r, 0) << '\n';
        }
        else {
            cin >> t;
        }
    }
    return 0;
}