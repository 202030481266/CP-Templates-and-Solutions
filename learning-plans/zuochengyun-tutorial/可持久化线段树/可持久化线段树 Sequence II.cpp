// https://acm.hdu.edu.cn/showproblem.php?pid=5919

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 2e5 + 7;
const int N = maxn * 37;
int root[maxn], tot, n, m;
int ls[N], rs[N], sum[N], a[maxn], pos[maxn];

void pushup(int rt) {
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
}
int build(int l, int r) {
    int rt = ++tot;
    if (l == r) {
        sum[rt] = 0;
        return rt;
    }
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    pushup(rt);
    return rt;
}

int update(int rt, int l, int r, int p, int val) {
    int c = ++tot;
    ls[c] = ls[rt], rs[c] = rs[rt], sum[c] = sum[rt];
    if (l == r) {
        sum[c] = val;
        return c; 
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[c] = update(ls[c], l, mid, p, val);
    else rs[c] = update(rs[c], mid + 1, r, p, val);
    pushup(c);
    return c;
}

int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return sum[rt];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(ls[rt], l, mid, L, R);
    else if (L > mid) return query(rs[rt], mid + 1, r, L, R);
    else return query(ls[rt], l, mid, L, mid) + query(rs[rt], mid + 1, r, mid + 1, R);
}

int kth(int rt, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (sum[ls[rt]] >= k) return kth(ls[rt], l, mid, k);
    else return kth(rs[rt], mid + 1, r, k - sum[ls[rt]]);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t, lastans = 0;
    cin >> t;
    for (int cas = 1; cas <= t; ++cas) {
        cin >> n >> m;
        tot = 0;
        lastans = 0;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        root[n+1] = build(1, n);
        memset(pos, -1, sizeof(pos));
        for (int i = n; i >= 1; --i) {
            if (pos[a[i]] == -1) {
                pos[a[i]] = i;
                root[i] = update(root[i+1], 1, n, i, 1);
            }
            else {
                root[i] = update(root[i+1], 1, n, pos[a[i]], 0);
                root[i] = update(root[i], 1, n, i, 1);
                pos[a[i]] = i;
            }
        }
        int l, r, x, y;
        cout << "Case #" << cas << ": ";
        for (int i = 1; i <= m; ++i) {
            cin >> x >> y;
            x = (x + lastans) % n + 1;
            y = (y + lastans) % n + 1;
            l = min(x, y);
            r = max(x, y);
            int sz = query(root[l], 1, n, l, r);
            int k = (sz + 1) / 2;
            int ans = kth(root[l], 1, n, k);
            if (i == m) cout << ans << '\n';
            else cout << ans << ' ';
            lastans = ans;
        }
    }
} 

