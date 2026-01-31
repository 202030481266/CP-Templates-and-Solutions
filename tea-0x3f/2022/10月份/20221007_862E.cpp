// Problem: E. Mahmoud and Ehab and the function
// Contest: Codeforces - Codeforces Round 435 (Div. 2)
// URL: https://codeforces.com/problemset/problem/862/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 100005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, m, a[MAXN], b[MAXN];
ll sa, sb[MAXN], arr[MAXN];
int N, q;

void cal() {
    int p = lower_bound(arr, arr + N, -sa) - arr;
    ll res = 0x3f3f3f3f3f3f3f3f;
    if (p < N) res = min(res, arr[p] + sa);
    if (p > 0) res = min(res, -arr[p - 1] - sa);
    cout << res << '\n';
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sa += (i & 1 ? a[i] : -a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
        sb[i] = sb[i - 1] + (i & 1 ? -b[i] : b[i]);
    }
    N = m - n + 1;
    for (int i = 0; i < N; ++i) {
        arr[i] = (i & 1 ? sb[i] - sb[n + i] : sb[n + i] - sb[i]);
    }
    sort(arr, arr + N);
    cal();
    for (int i = 0, l, r, x; i < q; ++i) {
        cin >> l >> r >> x;
        if ((l & 1) && (r & 1)) sa += x;
        if ((l & 1) == 0 && (r & 1) == 0) sa -= x;
        cal();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}