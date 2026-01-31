#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 2e4 + 7;
const int N = 25 * maxn;

struct Node {
    ll sum, lsum, rsum;
    int ls, rs;
} tr[N];

int n, m, tot, a[maxn], b[maxn], root[maxn];

void pushup(int rt) {
    tr[rt].sum = tr[tr[rt].ls].sum + tr[tr[rt].rs].sum;  
    tr[rt].lsum = max(tr[tr[rt].ls].lsum, tr[tr[rt].ls].sum + tr[tr[rt].rs].lsum);
    tr[rt].rsum = max(tr[tr[rt].rs].rsum, tr[tr[rt].rs].sum + tr[tr[rt].ls].rsum);
}

int build(int l, int r) {
    int rt = ++tot;
    if (l == r) {
        tr[rt].sum = tr[rt].lsum = tr[rt].rsum = 1;
        return rt;
    }
    int mid = (l + r) >> 1;
    tr[rt].ls = build(l, mid);
    tr[rt].rs = build(mid + 1, r);
    pushup(rt);
    return rt;
}

int update(int rt, int l, int r, int p, int val) {
    int c = ++tot;
    tr[c] = tr[rt];
    if (l == r) {
        tr[c].sum = tr[c].lsum = tr[c].rsum = val;
        return c;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) tr[c].ls = update(tr[c].ls, l, mid, p, val);
    else tr[c].rs = update(tr[c].rs, mid + 1, r, p, val);
    pushup(c);
    return c;
}

Node query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tr[rt];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(tr[rt].ls, l, mid, L, R);
    if (L > mid) return query(tr[rt].rs, mid + 1, r, L, R);
    Node left = query(tr[rt].ls, l, mid, L, mid);
    Node right = query(tr[rt].rs, mid + 1, r, mid + 1, R);
    Node res;
    res.sum = left.sum + right.sum;
    res.lsum = max(left.lsum, left.sum + right.lsum);
    res.rsum = max(right.rsum, right.sum + left.rsum);
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = i;
    }
    sort(b, b + n, [&](int x, int y) {
        return a[x] < a[y];
    });
    root[0] = build(0, n-1);
    for (int i = 1; i < n; ++i) {
        root[i] = update(root[i-1], 0, n-1, b[i-1], -1);
    }
    cin >> m;
    int lastans = 0;
    vector<int> q(4);
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> q[j];
            q[j] = (q[j] + lastans) % n;
        }
        sort(q.begin(), q.end());
        int l = -1, r = n;
        ll res = 0;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            Node left = query(root[mid], 0, n-1, q[0], q[1]);
            Node right = query(root[mid], 0, n-1, q[2], q[3]);
            if (q[2] == q[1] + 1) res = 0;
            else { 
                Node middle = query(root[mid], 0, n-1, q[1]+1, q[2]-1);
                res = middle.sum;
            }
            if (res + left.rsum + right.lsum >= 0) {
                l = mid;
            }
            else r = mid;
        }
        lastans = a[b[l]];
        cout << lastans << '\n';
    }
}