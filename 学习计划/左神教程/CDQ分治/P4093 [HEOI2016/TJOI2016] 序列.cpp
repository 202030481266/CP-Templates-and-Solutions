// https://www.luogu.com.cn/problem/P4093
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

static constexpr int maxn = 1e5 + 5;

int n, m, N; 
int dp[maxn];
array<int, 4> a[maxn];

int fenwick[maxn];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int val) {
    for (; x <= N; x += lowbit(x)) {
        fenwick[x] = max(fenwick[x], val);
    }
}

int query(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) {
        res = max(res, fenwick[x]);
    }
    return res;
}

void clear(int x) {
    for (; x <= N; x += lowbit(x)) {
        fenwick[x] = 0;
    }
}

void cdq(int l, int r) {
    if (l == r) {
        dp[a[l][3]] = max(dp[a[l][3]], 1);
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid);
    sort(a + l, a + mid + 1, [&](const auto& x, const auto& y) {
        return x[0] == y[0] ? x[3] < y[3] : x[0] < y[0]; // sort by cj
    });
    sort(a + mid + 1, a + r + 1, [&](const auto& x, const auto& y){
        return x[2] == y[2] ? x[3] < y[3] : x[2] < y[2]; // sort by mni
    });
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && a[p1][0] <= a[p2][2]) {
            add(a[p1][1], dp[a[p1][3]]);
            p1++;
        }
        dp[a[p2][3]] = max(dp[a[p2][3]], query(a[p2][0]) + 1);
        p2++;
    }
    for (int i = l; i < p1; ++i) clear(a[i][1]);
    sort(a + mid + 1, a + r + 1, [&](const auto& x, const auto& y){
        return x[3] < y[3]; 
    });
    cdq(mid + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    // j < i, mxj <= ci, cj <= mni, 三维偏序
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0];
        a[i][1] = a[i][0];
        a[i][2] = a[i][0];
        a[i][3] = i;
        N = max(N, a[i][0]);
    }
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        a[x][1] = max(a[x][1], y);
        a[x][2] = min(a[x][2], y);
        N = max(N, a[x][1]);
    }
    cdq(1, n);
    int ans = 1;
    for (int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
    cout << ans << '\n';
}