// https://www.luogu.com.cn/problem/P4390
#include <bits/stdc++.h>
using namespace std;

static constexpr int maxn = 200007;
static constexpr int maxv = 2000007;
int n, ans[maxn], m = 0, q = 0;
int fenwick[maxv];
array<int, 4> a[maxn], temp[maxn];

int lowbit(int i) {
    return i & -i;
}

void add(int p, int v) {
    for (int i = p; i <= n; i += lowbit(i)) {
        fenwick[i] += v;
    }
}

int query(int p) {
    int res = 0;
    for (int i = p; i; i -= lowbit(i)) {
        res += fenwick[i];
    }
    return res;
}

void add(int x, int y, int w, int id) {
    a[++m][0] = x;
    a[m][1] = y;
    a[m][2] = w;
    a[m][3] = id;
}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    int p1 = l, p2 = mid + 1, p = l;
    while (p2 <= r) {
        while (p1 <= mid && a[p1][0] <= a[p2][0]) {
            if (a[p1][3] == 0) {
                add(a[p1][1], a[p1][2]);
            }
            p1++;
        }
        if (a[p2][3] > 0) {
            ans[a[p2][3]] += a[p2][2] * query(a[p2][1]);
        }
        p2++;
    }
    for (int i = l; i < p1; ++i) {
        if (a[i][3] == 0) add(a[i][1], -a[i][2]);
    }
    p1 = l, p2 = mid + 1;
    while (p1 <= mid && p2 <= r) {
        if (a[p1][0] <= a[p2][0]) temp[p++] = a[p1++];
        else temp[p++] = a[p2++];
    }
    while (p1 <= mid) temp[p++] = a[p1++];
    while (p2 <= r) temp[p++] = a[p2++];
    for (int i = l; i <= r; ++i) a[i] = temp[i];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t, x, y, w;
    cin >> t >> n;
    while (true) {
        cin >> t;
        if (t == 1) {
            cin >> x >> y >> w;
            add(x, y, w, 0);
        }
        else if (t == 2) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            add(x2, y2, 1, ++q);
            add(x2, y1 - 1, -1, q);
            add(x1 - 1, y2, -1, q);
            add(x1 - 1, y1 - 1, 1, q);
        }
        else break;
    }
    cdq(1, m);
    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << '\n';
    }
}