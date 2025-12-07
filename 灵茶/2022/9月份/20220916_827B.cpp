// Problem: B. High Load
// Contest: Codeforces - Codeforces Round 423 (Div. 1, rated, based on VK Cup Finals)
// URL: https://codeforces.com/problemset/problem/827/B
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300005;
static constexpr int MOD = 998244353;
static constexpr int INF = 0x3f3f3f3f;

int n, k;

void solve() {
    cin >> n >> k;
    int mx = (n + k - 2) / k;
    if ((mx - 1) * k + 1 == n - 1) cout << 2 * mx - 1 << '\n';
    else cout << 2 * mx << '\n';
    for (int i = 2; i <= k + 1; ++i) {
        cout << 1 << ' ' << i << '\n';
    }
    for (int i = k + 2; i <= n; ++i) {
        cout << i - k << ' ' << i << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}


