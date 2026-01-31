// https://www.luogu.com.cn/problem/P3293

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 经典的位运算二分技巧：判断数位是否能够等于1或者0，然后使用数据结构加速

const int maxn = 2e5 + 7;
const int N = maxn * 22;
const int B = 20;
int n, m, tot;
int root[maxn], ls[N], rs[N], sum[N];

int build(int l, int r) {
    int rt = ++tot;
    if (l == r) return rt;
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    return rt;
}

int update(int rt, int l, int r, int p, int val) {
    int c = ++tot;
    ls[c] = ls[rt], rs[c] = rs[rt], sum[c] = sum[rt];
    if (l == r) {
        sum[c] += val;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p, val);
    else rs[c] = update(rs[c], mid + 1, r, p, val);
    sum[c] = sum[ls[c]] + sum[rs[c]];
    return c;
}

int query(int x, int y, int l, int r, int L, int R) {
    if (L <= l && r <= R) return sum[y]-sum[x];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(ls[x], ls[y], l, mid, L, R);
    else if (L > mid) return query(rs[x], rs[y], mid + 1, r, L, R);
    else return query(ls[x], ls[y], l, mid, L, mid) + query(rs[x], rs[y], mid + 1, r, mid + 1, R);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    root[0] = build(0, 100000);
    for (int i = 1, num; i <= n; ++i) {
        cin >> num;
        root[i] = update(root[i - 1], 0, 100000, num, 1);
    }
    for (int i = 1, b, x, l, r, L, R; i <= m; ++i) {
        cin >> b >> x >> l >> r;
        // find best k that maximize b ^ (x + k)
        // assume that x + k = y, if (y >> i) & 1 == b, judge if there exist
        int ans = 0;
        for (int j = B, bit; j >= 0; --j) {
            bit = (b >> j) & 1;
            if (bit ^ 1) {
                L = ans | (1 << j);
                R = ans | (1 << j) | ((1 << j) - 1);
            }
            else {
                L = ans;
                R = ans | ((1 << j) - 1);
            }
            L -= x;
            R -= x;
            if (L < 0) L = 0;
            if (R > 100000) R = 100000;
            int res = 0;
            if (R >= L) res = query(root[l-1], root[r], 0, 100000, L, R);
            if (res > 0) {
                ans |= ((bit ^ 1) << j);
            }
            else {
                ans |= (bit << j);
            }
        }
        cout << (ans^b) << '\n';
    }
}
