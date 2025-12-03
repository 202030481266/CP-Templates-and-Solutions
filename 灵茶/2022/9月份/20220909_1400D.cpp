// Problem: D. Zigzags
// Contest: Codeforces - Educational Codeforces Round 94 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1400/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
// 相似题目 https://codeforces.com/contest/1677/problem/A

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MAXN = 3500;

int n, arr[MAXN];
ll cnt[MAXN], sum[MAXN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) cnt[i] = sum[i] = 0;
    for (int i = 1; i <= n; ++i) ++sum[arr[i]];    
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        --sum[arr[i]];
        ll cur = 0;
        for (int j = i - 1; j >= 1; --j) {
            if (arr[j] == arr[i]) ans += cur;
            cur += sum[arr[j]];
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}