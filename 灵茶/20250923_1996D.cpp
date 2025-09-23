#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n, x;

void solve() {
    cin >> n >> x;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j * i <= n && j + i <= x; ++j) {
             ans += min(x - i - j, (n - i * j) / (i + j));
        }
    }
    cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
