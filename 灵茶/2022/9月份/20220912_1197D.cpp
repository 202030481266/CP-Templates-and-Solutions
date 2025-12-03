// Problem: D. Yet Another Subarray Problem
// Contest: Codeforces - Educational Codeforces Round 69 (Rated for d. 2)
// URL: https://codeforces.com/problemset/problem/1197/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

constexpr int MAXN = 300005;
int n, m, k;
int arr[MAXN];
ll sum[MAXN], mn[20];

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + arr[i];
    memset(mn, 0x3f, sizeof(mn));
    mn[0] = 0;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int d = i / m, r = i % m;
        ll cur = sum[i] - 1ll * k * d;
        for (int j = 0; j < r; ++j) ans = max(ans, cur - mn[j] - k);
        for (int j = r; j < m; ++j) ans = max(ans, cur - mn[j]);
        mn[r] = min(mn[r], cur);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}