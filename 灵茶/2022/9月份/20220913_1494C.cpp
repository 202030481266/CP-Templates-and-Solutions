// Problem: C. 1D Sokoban
// Contest: Codeforces - Educational Codeforces Round 105 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1494/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, m, a[MAXN], b[MAXN];
int x[MAXN], y[MAXN], nx, ny;  

int cal() {
    int l = 1, p = 1, q = 1, sum = 0, res = 0;
    while (p <= nx && q <= ny) {
        if (x[p] == y[q]) {
            ++sum;
            ++p;
            ++q;
        }
        else if (x[p] > y[q]) ++q;
        else ++p;
    }
    p = 1;
    res = sum;
    for (int i = 1; i <= ny; ++i) {
        while (p <= nx && x[p] <= y[i]) { // [1, p)
            if (x[p] == y[i]) --sum;
            ++p;
        }
        while (y[i] - y[l] + 1 > p - 1) ++l;
        res = max(res, sum + i - l + 1);
    }
    return res;
}

void solve() {
    cin >> n >> m;    
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    int p = 1, q = 1, ans = 0;
    while (p <= n && a[p] < 0) ++p;
    while (q <= m && b[q] < 0) ++q;
    if (p > 1 && q > 1) {
        for (int i = p - 1, j = 1; i >= 1; --i, ++j) x[j] = -a[i];
        for (int i = q - 1, j = 1; i >= 1; --i, ++j) y[j] = -b[i];
        nx = p - 1; // [1, p)
        ny = q - 1; // [1, q)
        ans += cal();
    }
    if (p <= n && q <= m) {
        for (int i = p; i <= n; ++i) x[i - p + 1] = a[i];
        for (int i = q; i <= m; ++i) y[i - q + 1] = b[i];
        nx = n - p + 1;
        ny = m - q + 1;
        ans += cal();
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}